/** @file
    @brief Implementation

    @date 2014

    @author
    Ryan Pavlik
    <ryan@sensics.com>
    <http://sensics.com>
*/

/*
// Copyright 2014 Sensics, Inc.
//
// All rights reserved.
//
// (Final version intended to be licensed under
// the Apache License, Version 2.0)
*/

/* Internal Includes */
#include <osvr/ClientKit/ContextC.h>
#include <osvr/ClientKit/InterfaceC.h>
#include <osvr/ClientKit/InterfaceCallbackC.h>

/* Library/third-party includes */
/* none */

/* Standard includes */
#include <stdio.h>

void myButtonCallback(void *userdata, const OSVR_TimeValue *timestamp,
                      const OSVR_ButtonReport *report) {
    printf("Got report: button is %s\n",
           (report->state ? "pressed" : "released"));
}

int main() {
    OSVR_ClientContext context =
        osvrClientInit("org.opengoggles.exampleclients.ButtonCallback", 0);

    OSVR_ClientInterface button1 = NULL;
    /* This is just one of the paths: specifically, the Hydra's left
     * controller's button labelled "1". More are in the docs and/or listed on
     * startup
     */
    osvrClientGetInterface(context, "/controller/left/1", &button1);

    osvrRegisterButtonCallback(button1, &myButtonCallback, NULL);

    /* Pretend that this is your application's mainloop. */
    int i;
    for (i = 0; i < 1000000; ++i) {
        osvrClientUpdate(context);
    }

    osvrClientShutdown(context);
    printf("Library shut down, exiting.\n");
    return 0;
}
