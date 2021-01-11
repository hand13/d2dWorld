#pragma once
#include <windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>
HRESULT decodeImage(const WCHAR * fileName,IWICBitmapSource ** bitmapSource);