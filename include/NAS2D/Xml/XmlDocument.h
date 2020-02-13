#pragma once

#include "XmlNode.h"

namespace NAS2D {
namespace Xml {

/**
 * Always the top level node. A document binds together all the XML pieces.
 */
class XmlDocument : public XmlNode
{
public:
	XmlDocument();
	explicit XmlDocument(const std::string& documentName);

	XmlDocument(const XmlDocument& copy);
	XmlDocument& operator=(const XmlDocument& copy);

	virtual ~XmlDocument() {}

	const char* parse(const char* p, void* data = nullptr) override;

	const XmlElement* rootElement() const;
	XmlElement* rootElement();

	bool error() const;
	const std::string& errorDesc() const;
	int errorId() const;
	int errorRow() const;
	int errorCol() const;

	void clearError();

	const XmlDocument* toDocument() const override { return this; }
	XmlDocument* toDocument() override { return this; }

	bool accept(void* content) const override;
	void write(std::string& buf, int depth = 0) const override;

public:
	void error(XmlErrorCode err, const char* errorLocation, void* prevData);

protected:
	XmlNode* clone() const override;
	void streamIn(std::istream& in, std::string& tag) override;

private:
	void copyTo(XmlDocument* target) const;

private:
	int					_errorId;

	bool				_error;

	std::string			_errorDesc;

	XmlBase::ParseLocation	_errorLocation;
};

} // namespace Xml
} // namespace NAS2D
