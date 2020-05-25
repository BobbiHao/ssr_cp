#ifndef UTILS_HPP
#define UTILS_HPP

#include "Global.h"
#include <QApplication>

std::vector<QRect> GetScreenGeometries() {
    std::vector<QRect> screen_geometries;
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    for(QScreen *screen :  QApplication::screens()) {
        QRect geometry = screen->geometry();
        qreal ratio = screen->devicePixelRatio();
        screen_geometries.emplace_back(geometry.x(), geometry.y(), lrint((qreal) geometry.width() * ratio), lrint((qreal) geometry.height() * ratio));
    }
#else
    for(int i = 0; i < QApplication::desktop()->screenCount(); ++i) {
        screen_geometries.push_back(QApplication::desktop()->screenGeometry(i));
    }
#endif
    return screen_geometries;
}

QRect CombineScreenGeometries(const std::vector<QRect>& screen_geometries) {
    QRect combined_geometry;
    for(const QRect &geometry : screen_geometries) {
        combined_geometry |= geometry;
    }
    return combined_geometry;
}

// This does some sanity checking on the rubber band rectangle before creating it.
// Rubber bands with width or height zero or extremely large appear to cause problems.
QRect ValidateRubberBandRectangle(QRect rect) {
    std::vector<QRect> screen_geometries = GetScreenGeometries();
    QRect combined_geometry = CombineScreenGeometries(screen_geometries);
    return rect.normalized() & combined_geometry.adjusted(-10, -10, 10, 10);
}

QRect MapToLogicalCoordinates(const QRect& rect) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    for(QScreen *screen :  QApplication::screens()) {
        QRect geometry = screen->geometry();
        qreal ratio = screen->devicePixelRatio();
        QRect physical_geometry(geometry.x(), geometry.y(), lrint((qreal) geometry.width() * ratio), lrint((qreal) geometry.height() * ratio));
        if(physical_geometry.contains(rect.center())) {
            return QRect(
                        geometry.x() + lrint((qreal) (rect.x() - physical_geometry.x()) / ratio - 0.4999),
                        geometry.y() + lrint((qreal) (rect.y() - physical_geometry.y()) / ratio - 0.4999),
                        lrint((qreal) rect.width() / ratio - 0.4999),
                        lrint((qreal) rect.height() / ratio - 0.4999));
        }
    }
#endif
    return rect;
};


#endif // UTILS_HPP
