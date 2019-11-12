#pragma once
#include "CStyle.h"
#include "ILineStyle.h"

class CLineStyle
	: public ILineStyle
	, public CStyle
{
public:
	CLineStyle();
	CLineStyle(RGBAColor color, double lineSize);
	virtual ~CLineStyle() = default;

	virtual std::optional<double> GetLineSize() const override;
	virtual void SetLineSize(double lineSize) override;

	virtual std::optional<bool> IsEnabled() const override;
	virtual void Enable(bool enable) override;

	virtual std::optional<RGBAColor> GetColor() const override;
	virtual void SetColor(RGBAColor color) override;

private:
	std::optional<double> m_lineSize = std::nullopt;
};
