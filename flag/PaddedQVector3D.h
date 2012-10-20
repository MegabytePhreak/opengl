#ifndef _PADDEDQVECTOR3D_H
#define _PADDEDQVECTOR3D_H

#include <QVector3D>

class PaddedQVector3D : QVector3D
{
public:
    PaddedQVector3D();
    PaddedQVector3D(qreal xpos, qreal ypos, qreal zpos);
    explicit PaddedQVector3D(const QPoint& point);
    explicit PaddedQVector3D(const QPointF& point);
    PaddedQVector3D(const QVector2D& vector);
    PaddedQVector3D(const QVector2D& vector, qreal zpos);
    explicit PaddedQVector3D(const QVector4D& vector);

private:

    float dummy;
};

Q_DECLARE_TYPEINFO(PaddedQVector3D, Q_MOVABLE_TYPE);

inline PaddedQVector3D::PaddedQVector3D()
    : QVector3D(),dummy(0.0f)
{}

inline PaddedQVector3D::PaddedQVector3D(qreal xpos, qreal ypos, qreal zpos)
    : QVector3D(xpos,ypos,zpos),dummy(0.0f)
{}

inline PaddedQVector3D::PaddedQVector3D(const QPoint& point)
    : QVector3D(point), dummy(0.0f)
{}

inline PaddedQVector3D::PaddedQVector3D(const QPointF& point) 
    : QVector3D(point), dummy(0.0f)
{}

inline PaddedQVector3D::PaddedQVector3D(const QVector2D & vector)
    : QVector3D( vector), dummy(0.0f)
{}

inline PaddedQVector3D::PaddedQVector3D(const QVector2D & vector, qreal zpos) 
    : QVector3D(vector, zpos), dummy(0.0f)
{}

inline PaddedQVector3D::PaddedQVector3D(const QVector4D & vector)
    : QVector3D(vector), dummy(0.0f)
{}

#endif

