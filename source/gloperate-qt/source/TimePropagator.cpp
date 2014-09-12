/******************************************************************************\
 * gloperate
 *
 * Copyright (C) 2014 Computer Graphics Systems Group at the 
 * Hasso-Plattner-Institut (HPI), Potsdam, Germany.
\******************************************************************************/
#include <gloperate-qt/TimePropagator.h>
#include <chrono>


namespace gloperate_qt
{


/**
*  @brief
*    Constructor
*/
TimePropagator::TimePropagator(gloperate_qt::QtOpenGLWindowBase * window, gloperate::AbstractVirtualTimeCapability * capability)
: m_window(window)
, m_capability(capability)
, m_timer(new QTimer())
, m_time(false, true)
{
    // Connect to timer signal
    connect(m_timer.data(), SIGNAL(timeout()), this, SLOT(update()));

    // Start timer
    m_timer->setSingleShot(false);
    m_timer->start(0);
    m_time.start();
}

/**
*  @brief
*    Called by the timer when the timer has elapsed
*/
void TimePropagator::update()
{
    // Calculate time delta
    float delta = std::chrono::duration_cast<std::chrono::duration<float>>(m_time.elapsed()).count();
    m_time.reset();

    // Propagate new time
    m_capability->update(delta);

    // Update window
    m_window->updateGL();
}


} // namespace gloperate_qt
