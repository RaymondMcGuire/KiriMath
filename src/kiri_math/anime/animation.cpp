/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-08 16:44:29 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2020-04-08 16:44:29 
 */
#include <kiri_math/pch.h>
#include <kiri_math/anime/animation.h>
#include <kiri_math/timer.h>

#include <kiri_math/private_helpers.h>

using namespace kiri_math;

Frame::Frame()
{
}

Frame::Frame(int newIndex, double newTimeIntervalInSeconds)
    : index(newIndex), timeIntervalInSeconds(newTimeIntervalInSeconds)
{
}

double Frame::timeInSeconds() const
{
    return index * timeIntervalInSeconds;
}

void Frame::advance()
{
    ++index;
}

void Frame::advance(int delta)
{
    index += delta;
}

Frame &Frame::operator++()
{
    advance();
    return *this;
}

Frame Frame::operator++(int i)
{
    UNUSED_VARIABLE(i);

    Frame result = *this;
    advance();
    return result;
}

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::update(const Frame &frame)
{
#ifdef KIRI_LOGGING
    Timer timer;

    KIRI_INFO << "Begin updating frame: " << frame.index
              << " timeIntervalInSeconds: " << frame.timeIntervalInSeconds
              << " (1/" << 1.0 / frame.timeIntervalInSeconds
              << ") seconds";
#endif
    onUpdate(frame);

#ifdef KIRI_LOGGING
    KIRI_INFO << "End updating frame (took " << timer.durationInSeconds()
              << " seconds)";
#endif
}
