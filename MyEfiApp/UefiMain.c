#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/UsbIo.h>
#include <Protocol/DevicePath.h>

#define BUFFER_SIZE (1 << 6)

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_USB_IO_PROTOCOL      *UsbIo;
  EFI_USB_INTERFACE_DESCRIPTOR InterfaceDesc;
  EFI_USB_ENDPOINT_DESCRIPTOR EndpointDesc;
  EFI_STATUS                Status;
  UINTN Index;
 
  Status = gBS->LocateProtocol(
    &gEfiUsbIoProtocolGuid,
    NULL,
    (VOID**) &UsbIo
  );

  if (EFI_ERROR(Status)) {
    Print(L"Failed to locate USB protocol: %d\n", Status);
    return Status;
  }

  Status = UsbIo->UsbGetInterfaceDescriptor(
    UsbIo,
    &InterfaceDesc
  );

  for (Index = 0; Index < InterfaceDesc.NumEndpoints; Index++) {
    Status = UsbIo->UsbGetEndpointDescriptor(
      UsbIo,
      Index,
      &EndpointDesc
    );

    Print(L"\n");
    Print(L"#%ud:\n", Index);
    Print(L"\tStatus:%ud\n", Status);
    Print(L"\tLength:%ud\n", EndpointDesc.Length);
    Print(L"\tDescriptorType:%ud\n", EndpointDesc.DescriptorType);
    Print(L"\tEndpointAddress:%ud\n", EndpointDesc.EndpointAddress);
    Print(L"\tAttributes:%ud\n", EndpointDesc.Attributes);
    Print(L"\tMaxPacketSize:%ud\n", EndpointDesc.MaxPacketSize);
    Print(L"\tInterval:%ud\n", EndpointDesc.Interval);
    Print(L"\n");
  }

  return EFI_SUCCESS;
}
