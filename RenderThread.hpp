/*
 *  HDRMerge - HDR exposure merging software.
 *  Copyright 2012 Javier Celaya
 *  jcelaya@gmail.com
 *
 *  This file is part of HDRMerge.
 *
 *  HDRMerge is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  HDRMerge is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with HDRMerge. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _RENDERTHREAD_H_
#define _RENDERTHREAD_H_

#include <QThread>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>


namespace hdrmerge {

class ImageStack;

class RenderThread : public QThread {
public:
    RenderThread(ImageStack * es, float gamma = 1.0f, QObject *parent = 0);
    ~RenderThread();

public slots:
    void setGamma(float g);
    void setImageViewport(int x, int y, int w, int h);
    void addPixels(int i, int x, int y, int radius);
    void removePixels(int i, int x, int y, int radius);

signals:
    void renderedImage(unsigned int x, unsigned int y, unsigned int width, unsigned int height, const QImage & image);

protected:
    void run();

private:
    Q_OBJECT

    QMutex mutex;
    QWaitCondition condition;
    bool restart;
    bool abort;
    ImageStack * images;
    unsigned int minx, miny, maxx, maxy;
    int gamma[65536];

    void doRender(unsigned int minx, unsigned int miny, unsigned int maxx, unsigned int maxy, QImage & image, bool ignoreRestart = false);
    QRgb rgb(size_t col, size_t row) const;
};

} // namespace hdrmerge

#endif // _RENDERTHREAD_H_
