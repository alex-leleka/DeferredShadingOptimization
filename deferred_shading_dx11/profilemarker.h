#pragma once

#include <atlbase.h> // Contains the declaration of CComPtr.
#include <memory>

struct ID3D11DeviceContext;
struct ID3DUserDefinedAnnotation;

class CProfileMarker
{
    class CScopedMarker
    {
    public:
        CScopedMarker(_In_ LPCWSTR Name, CProfileMarker * pPerf);
        ~CScopedMarker();
    private:
        CProfileMarker * m_pPerf;
    };
public:
    void Init(ID3D11DeviceContext* d3dDeviceContext);
    void BeginEvent(_In_ LPCWSTR Name);
    void EndEvent();
    void SetMarker(_In_ LPCWSTR Name);
    std::unique_ptr<CScopedMarker> AddScopedMarker(_In_ LPCWSTR Name);
private:
    CComPtr<ID3DUserDefinedAnnotation> m_pPerf;
};

inline std::unique_ptr<CProfileMarker::CScopedMarker> CProfileMarker::AddScopedMarker(LPCWSTR Name)
{
    return std::make_unique<CProfileMarker::CScopedMarker>(Name, this);
}