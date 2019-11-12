#pragma once
#include "IStyle.h"

class CStyleGroup : public IStyle
{
public:
	CStyleGroup(const std::vector<std::shared_ptr<IStyle>>& styleArr);

	virtual std::optional<bool> IsEnabled() const override;
	virtual void Enable(bool enable) override;
	virtual std::optional<RGBAColor> GetColor() const override;
	virtual void SetColor(RGBAColor color) override;

private:
	std::vector<std::shared_ptr<IStyle>> m_styleArr;
};
