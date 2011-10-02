//////////////////////////////////////////////////////////////////////////////
// Model: fsa_eos.qm
// File:  ./usbtask.cpp
//
// This file has been generated automatically by QP Modeler (QM).
// DO NOT EDIT THIS FILE MANUALLY.
//
// Please visit www.state-machine.com/qm for more information.
//////////////////////////////////////////////////////////////////////////////
#include "Usb.h"
#include "qp_port.h"
#include "bsp.h"
#include "fsa.h"

Q_DEFINE_THIS_FILE

// mult.reconnect - /2 rare
//
#define USB_TICK_TIME BSP_TICKS_PER_SEC/5   //Usb.Task() tick time

//Usbtask Class
// $(AOs::Usbtask) ...........................................................
/// AO to run USB Task. To be moved somewhere else.
class Usbtask : public QActive {
private:
    QTimeEvt usb_tick;

public:
    Usbtask() : QActive((QStateHandler)&Usbtask::initial), usb_tick(USB_TICK_SIG) {
    }

protected:
    static QState initial(Usbtask *me, QEvent const *e);
    static QState usb_task(Usbtask *me, QEvent const *e);
};

//Local objects
static Usbtask l_usbtask;

//Global objects
QActive * const AO_Usbtask = &l_usbtask;

//Lights class definition
// $(AOs::Usbtask) ...........................................................

// $(AOs::Usbtask::Statechart) ...............................................
// @(/2/3/2/0)
QState Usbtask::initial(Usbtask *me, QEvent const *e) {
    me->usb_tick.postIn(me, USB_TICK_TIME);
    return Q_TRAN(&Usbtask::usb_task);
}
// $(AOs::Usbtask::Statechart::usb_task) .....................................
QState Usbtask::usb_task(Usbtask *me, QEvent const *e) {
    switch (e->sig) {
        // @(/2/3/2/1)
        case Q_ENTRY_SIG: {
            //Notify(PSTR("AO_UT Entry\r\n"));
            return Q_HANDLED();
        }
        // @(/2/3/2/1/0)
        case USB_TICK_SIG: {
            //Notify(PSTR("AO_UT USB_TICK_SIG\r\n"));
            O_usb->Task();
            me->usb_tick.postIn(me, USB_TICK_TIME);

            return Q_HANDLED();
        }
    }
    return Q_SUPER(&QHsm::top);
}

