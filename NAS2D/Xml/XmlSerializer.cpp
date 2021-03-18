#include "XmlSerializer.h"

#include "../Filesystem.h"
#include "../Utility.h"

namespace NAS2D {
	Xml::XmlDocument openXmlFile(std::string filename, std::string rootElementName)
	{
		Xml::XmlDocument xmlDocument;
		xmlDocument.parse(Utility<Filesystem>::get().open(filename).raw_bytes());

		if (xmlDocument.error())
		{
			throw std::runtime_error(filename + " has malformed XML: Row: " + std::to_string(xmlDocument.errorRow()) + " Column: " + std::to_string(xmlDocument.errorCol()) + " : " + xmlDocument.errorDesc());
		}

		const auto* xmlRootElement = xmlDocument.firstChildElement(rootElementName);
		if (!xmlRootElement)
		{
			throw std::runtime_error(filename + " does not contain required root tag of <" + rootElementName + ">");
		}

		return xmlDocument;
	}
}
