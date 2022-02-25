#include "framework.h"
#include "CTimeManager.h"

CTimeManager::CTimeManager()
{
	m_llCurCount = {};
	m_llPrevCount = {};
	m_llFrequency = {};
	m_uiFPS = 0;
	m_dDT = 0;
	m_uiPlayTime = 0;
}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::Update()
{
	static unsigned int updateCount = 0;
	static double updateOneSecond = 0;

	QueryPerformanceCounter(&m_llCurCount); // ���� ī��Ʈ ����

	// ī��Ʈ ���� ���� ���� 1�ʴ� ������ ī��Ʈ�� �������ش�. -> ������Ʈ ���̿� ���ʰ� �������� �� �� ����.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount; // ���� ī��Ʈ ����

	// 1�ʿ� ��� ������Ʈ�� �ϳ�.
	++updateCount;
	updateOneSecond += m_dDT;
	if (updateOneSecond >= 1.0)
	{
		m_uiFPS = updateCount;
		m_uiPlayTime++;
		m_bIsSecond = true;

		updateOneSecond = 0;
		updateCount = 0;
	}
	else
	{
		m_bIsSecond = false;
	}
}

void CTimeManager::Init()
{
	QueryPerformanceCounter(&m_llPrevCount);		// ���� �ð��� ī��Ʈ ��
	QueryPerformanceFrequency(&m_llFrequency);	// 1�ʴ� �����ϴ� ī��Ʈ ��
}

void CTimeManager::SetPlayTime(unsigned int _playTime)
{
	m_uiPlayTime = _playTime;
}