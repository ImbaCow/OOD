#pragma once
#include "IStyle.h"

class CStyle : virtual public IStyle
{
public:
	CStyle();
	CStyle(RGBAColor color);
	virtual ~CStyle() = default;

	virtual std::optional<bool> IsEnabled() const override;
	virtual void Enable(bool enable = true) override;
	virtual std::optional<RGBAColor> GetColor() const override;
	virtual void SetColor(RGBAColor color) override;

private:
	bool m_isEnabled = false;
	std::optional<RGBAColor> m_color = std::nullopt;
};
