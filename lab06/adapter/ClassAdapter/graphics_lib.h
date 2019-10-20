#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>

namespace graphics_lib
{
using namespace std;

// ����� ��� ���������
class ICanvas
{
public:
	// ��������� ����� � ������� 0xRRGGBB
	virtual void SetColor(uint32_t rgbColor) = 0;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// ���������� ������ ��� ���������
class CCanvas : public ICanvas
{
public:
	void SetColor(uint32_t rgbColor) override
	{
		ostringstream ss;
		ss << setfill('0') << setw(8) << hex << rgbColor;
		cout << "SetColor (#" << ss.str() << ')' << endl;
		// TODO: ������� � output ���� � ���� ������ SetColor (#RRGGBB)
	}
	void MoveTo(int x, int y) override
	{
		cout << "MoveTo (" << x << ", " << y << ")" << endl;
	}
	void LineTo(int x, int y) override
	{
		cout << "LineTo (" << x << ", " << y << ")" << endl;
	}
};
} // namespace graphics_lib
