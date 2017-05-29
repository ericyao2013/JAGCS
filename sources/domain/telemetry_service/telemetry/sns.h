#ifndef SNS_H
#define SNS_H

// Qt
#include <QGeoCoordinate>

namespace domain
{
    class Sns // TODO: rename to SNS
    {
        Q_GADGET

        Q_PROPERTY(Fix fix READ fix CONSTANT)
        Q_PROPERTY(int satellitesVisible READ satellitesVisible CONSTANT)
        Q_PROPERTY(QGeoCoordinate coordinate READ coordinate CONSTANT)
        Q_PROPERTY(float altitude READ altitude CONSTANT)
        Q_PROPERTY(float course READ course CONSTANT)
        Q_PROPERTY(int eph READ eph CONSTANT)
        Q_PROPERTY(int epv READ epv CONSTANT)

    public:
        enum Fix
        {
            NoGps,
            NoFix,
            Fix2D,
            Fix3D
        };

        Sns(Fix fix = NoGps,
            short satellitesVisible = -1,
            const QGeoCoordinate& coordinate = QGeoCoordinate(),
            float course = 0,
            float groundSpeed = 0,
            int eph = 0, int epv = 0,
            quint64 time = 0);

        Fix fix() const;
        int satellitesVisible() const;
        QGeoCoordinate coordinate() const;
        float altitude() const;
        float course() const;
        float groundSpeed() const;
        int eph() const;
        int epv() const;
        quint64 time() const;

        bool operator ==(const Sns& other);

    private:
        Fix m_fix;
        int m_satellitesVisible;
        QGeoCoordinate m_coordinate;
        float m_course;
        float m_groundSpeed;
        int m_eph;
        int m_epv;
        quint64 m_time;

        Q_ENUM(Fix)
    };
}

#endif // SNS_H