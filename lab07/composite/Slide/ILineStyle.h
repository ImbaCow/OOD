#pragma once
#include "IStyle.h"

class ILineStyle : virtual public IStyle
{
public:
	virtual ~ILineStyle() = default;

	virtual std::optional<double> GetLineSize() const = 0;
	virtual void SetLineSize(double lineSize) = 0;
};
