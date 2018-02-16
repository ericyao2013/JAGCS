#include "gui_settings_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "units.h"

#include "presentation_context.h"
#include "translation_manager.h"
#include "gui_style_manager.h"

namespace
{
    QStringList availableSpeedUnits(
    {
        utils::Units::trSpeedUnits(utils::Units::Mps),
        utils::Units::trSpeedUnits(utils::Units::Kph),
        utils::Units::trSpeedUnits(utils::Units::Knots),
        utils::Units::trSpeedUnits(utils::Units::Mph)
    } );

    QStringList availableAltitudeUnits(
    {
        utils::Units::trDistanceUnits(utils::Units::Meters),
        utils::Units::trDistanceUnits(utils::Units::Kilometers),
        utils::Units::trDistanceUnits(utils::Units::Miles),
        utils::Units::trDistanceUnits(utils::Units::Feets)
    } );
}

using namespace presentation;

class GuiSettingsPresenter::Impl
{
public:
    TranslationManager translationManager;
    GuiStyleManager guiStyleManager;
};

GuiSettingsPresenter::GuiSettingsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

GuiSettingsPresenter::~GuiSettingsPresenter()
{}

void GuiSettingsPresenter::updateView()
{
    this->setViewProperty(PROPERTY(fullscreen), settings::Provider::value(settings::gui::fullscreen));

    const QStringList& locales = d->translationManager.avalibleLocales();
    int index = locales.indexOf(d->translationManager.currentLocale());
    this->setViewProperty(PROPERTY(locales), locales);
    this->setViewProperty(PROPERTY(localeIndex), index);

    this->setViewProperty(PROPERTY(availableSpeedUnits),
                          QVariant::fromValue(::availableSpeedUnits));
    this->setViewProperty(PROPERTY(availableAltitudeUnits),
                          QVariant::fromValue(::availableAltitudeUnits));

    this->setViewProperty(PROPERTY(uiSize),
                          settings::Provider::value(settings::gui::uiSize));
    this->setViewProperty(PROPERTY(paletteStyle),
                          settings::Provider::value(settings::gui::paletteStyle));
    this->setViewProperty(PROPERTY(rollInverted),
                          settings::Provider::value(settings::gui::fdRollInverted));
    this->setViewProperty(PROPERTY(speedStep),
                          settings::Provider::value(settings::gui::fdSpeedStep));
    this->setViewProperty(PROPERTY(speedUnits),
                          settings::Provider::value(settings::gui::fdSpeedUnits));
    this->setViewProperty(PROPERTY(altitudeStep),
                          settings::Provider::value(settings::gui::fdAltitudeStep));
    this->setViewProperty(PROPERTY(altitudeUnits),
                          settings::Provider::value(settings::gui::fdAltitudeUnits));
    this->setViewProperty(PROPERTY(relativeAltitude),
                          settings::Provider::value(settings::gui::fdRelativeAltitude));
    this->setViewProperty(PROPERTY(coordinatesDms),
                          settings::Provider::value(settings::gui::coordinatesDms));

    this->setViewProperty(PROPERTY(changed), false);
}

void GuiSettingsPresenter::save()
{
    settings::Provider::setValue(settings::gui::fullscreen,
                                 this->viewProperty(PROPERTY(fullscreen)).toBool());
    settings::Provider::setValue(settings::gui::uiSize,
                                 this->viewProperty(PROPERTY(uiSize)).toInt());
    settings::Provider::setValue(settings::gui::paletteStyle,
                                 this->viewProperty(PROPERTY(paletteStyle)));
    settings::Provider::setValue(settings::gui::fdRollInverted,
                                 this->viewProperty(PROPERTY(rollInverted)));
    settings::Provider::setValue(settings::gui::fdSpeedStep,
                                 this->viewProperty(PROPERTY(speedStep)));
    settings::Provider::setValue(settings::gui::fdSpeedUnits,
                                 this->viewProperty(PROPERTY(speedUnits)).value<
                                 utils::Units::SpeedUnits>());
    settings::Provider::setValue(settings::gui::fdAltitudeStep,
                                 this->viewProperty(PROPERTY(altitudeStep)));
    settings::Provider::setValue(settings::gui::fdAltitudeUnits,
                                 this->viewProperty(PROPERTY(altitudeUnits)).value<
                                 utils::Units::DistanceUnits>());
    settings::Provider::setValue(settings::gui::fdRelativeAltitude,
                                 this->viewProperty(PROPERTY(relativeAltitude)));
    settings::Provider::setValue(settings::gui::coordinatesDms,
                                 this->viewProperty(PROPERTY(coordinatesDms)));

    this->setViewProperty(PROPERTY(changed), false);

    const QStringList& locales = d->translationManager.avalibleLocales();
    QString locale = locales.value(this->viewProperty(PROPERTY(localeIndex)).toInt());
    d->translationManager.setCurrentLocale(locale);

    d->guiStyleManager.loadSavedSizings();
    d->guiStyleManager.loadSavedPalette();

    PresentationContext::saveWindowedGeometry();
    PresentationContext::updateGeometry();
}

void GuiSettingsPresenter::setFullscreen(bool fullscreen)
{
    PresentationContext::updateGeometry(fullscreen);
}

void GuiSettingsPresenter::setUiSize(int size)
{
    d->guiStyleManager.setSizings(size);
}

void GuiSettingsPresenter::setPalleteStyle(int paletteStyle)
{
    d->guiStyleManager.setPalette(static_cast<GuiStyleManager::PaletteStyle>(paletteStyle));
}
