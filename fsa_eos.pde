/* Circuits At Home */
/* Focus Stacking Assistant for Canon EOS Cameras */
/* Controls:
  LED -     D8
  NEAR button - D7
  FAR button  - D6
  GO button   - D5
  */
  

#include <Usb.h>
#include <ptp.h>

#include "qp_port.h"
#include "fsa.h"
#include "bsp.h"

// Local-scope objects -------------------------------------------------------

static QEvent const *l_ControlsQueueSto[30];
static QEvent const *l_CameraQueueSto[30];
static QEvent const *l_LightsQueueSto[30];
static QEvent const *l_UsbtaskQueueSto[30];
static QEvent const *l_CommandsQueueSto[30];

static QEvent        l_smlPoolSto[30];
static FocusMovedEvt  l_medPoolSto[10];  

//............................................................................
void setup() {
    BSP_init();                                          // initialize the BSP
    QF::init();       // initialize the framework and the underlying RT kernel
                                                  // initialize event pools...
    QF::poolInit(l_smlPoolSto, sizeof(l_smlPoolSto), sizeof(l_smlPoolSto[0]));
    QF::poolInit(l_medPoolSto, sizeof(l_medPoolSto), sizeof(l_medPoolSto[0]));
    
                                                // start the active objects...
    AO_Controls->start(7, l_ControlsQueueSto, Q_DIM(l_ControlsQueueSto), (void *)0, 0);
    AO_Commands->start(6, l_CommandsQueueSto, Q_DIM(l_CommandsQueueSto), (void *)0, 0);
    AO_Camera->start(5, l_CameraQueueSto, Q_DIM(l_CameraQueueSto), (void *)0, 0);
    AO_Usbtask->start(2, l_UsbtaskQueueSto, Q_DIM(l_UsbtaskQueueSto), (void *)0, 0);
    AO_Lights->start(1, l_LightsQueueSto, Q_DIM(l_LightsQueueSto), (void *)0, 0);

}

//////////////////////////////////////////////////////////////////////////////
// NOTE: Do not define the loop() function, because this function is
// already defined in the QP port to Arduino


