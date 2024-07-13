#if USB_CONFIGURE_EVENT
void USB_Configure_Event (void) {
    if (USB_Configuration) {                  /* Check if USB is configured */
        GetInReport();
        USB_WriteEP(0x81, &InReport, sizeof(InReport));
    }
}
#endif

void USB_EndPoint1 (DWORD event) {

    switch (event) {
        case USB_EVT_IN:
        GetInReport();
        USB_WriteEP(0x81, &InReport, sizeof(InReport));
    break;
    }
}