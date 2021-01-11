#include "image.h"
HRESULT decodeImage(const WCHAR * fileName,IWICBitmapSource ** bitmapSource) {
    IWICImagingFactory * imageFactory;
    IWICBitmapDecoder * decoder;
    IWICBitmapFrameDecode * frameDecoder;
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory
    ,NULL,CLSCTX_INPROC_SERVER,IID_IWICImagingFactory,(LPVOID*)&imageFactory);
    if(FAILED(hr)) {
        return hr;
    }
    hr = imageFactory->CreateDecoderFromFilename(fileName,NULL,GENERIC_READ,WICDecodeMetadataCacheOnDemand,&decoder);
    if(FAILED(hr)) {
        return hr;
    }
    decoder->GetFrame(0,&frameDecoder);
    *bitmapSource = frameDecoder;
    imageFactory->Release();
    decoder->Release();
    return 0;
}