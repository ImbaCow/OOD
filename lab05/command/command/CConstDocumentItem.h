#pragma once
#include "pch.h"
#include "IImage.h"
#include "IParagraph.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(const std::shared_ptr<const IImage>& imagePtr);
	CConstDocumentItem(const std::shared_ptr<const IParagraph>& paragraphPtr);
	virtual ~CConstDocumentItem() = default;

	std::shared_ptr<const IImage> GetImage() const;
	std::shared_ptr<const IParagraph> GetParagraph() const;

private:
	std::shared_ptr<const IImage> m_imagePtr = nullptr;
	std::shared_ptr<const IParagraph> m_paragraphPtr = nullptr;
};
