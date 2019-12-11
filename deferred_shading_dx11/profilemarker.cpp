#include "profilemarker.h"

#include <d3d11_1.h>
#include <stdexcept>

void CProfileMarker::Init(ID3D11DeviceContext* d3dDeviceContext)
{

    HRESULT hr = d3dDeviceContext->QueryInterface(__uuidof(m_pPerf), reinterpret_cast<void**>(&m_pPerf));
    if (FAILED(hr))
    {
        throw std::runtime_error("Error when QueryInterface ID3DUserDefinedAnnotation!!!");
    }
}

void CProfileMarker::BeginEvent(_In_ LPCWSTR Name)
{
    if (!m_pPerf)
        return;
    m_pPerf->BeginEvent(Name);
}

void CProfileMarker::EndEvent()
{
    if (!m_pPerf)
        return;
    m_pPerf->EndEvent();
}

void CProfileMarker::SetMarker(_In_ LPCWSTR Name)
{
    if (!m_pPerf)
        return;
    m_pPerf->SetMarker(Name);
}

CProfileMarker::CScopedMarker::CScopedMarker(LPCWSTR Name, CProfileMarker * pPerf)
    : m_pPerf(pPerf)
{
    m_pPerf->SetMarker(Name);
}

CProfileMarker::CScopedMarker::~CScopedMarker()
{
    m_pPerf->EndEvent();
}
