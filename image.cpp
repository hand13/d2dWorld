#include "image.h"
HRESULT decodeImage(const WCHAR * fileName,IWICBitmapSource ** bitmapSource) {
    IWICImagingFactory * imageFactory;
    IWICBitmapDecoder * decoder;
    IWICBitmapFrameDecode * frameDecoder;
    IWICFormatConverter * converter;
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
    hr = imageFactory->CreateFormatConverter(&converter);
    converter->Initialize(frameDecoder,GUID_WICPixelFormat32bppPBGRA,WICBitmapDitherTypeNone
    ,NULL,0.f,WICBitmapPaletteTypeMedianCut);
    *bitmapSource = converter;
    frameDecoder->Release();
    imageFactory->Release();
    decoder->Release();
    return 0;
}