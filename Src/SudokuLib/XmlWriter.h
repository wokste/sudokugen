#pragma once

#include <ostream>
#include <string>

enum class XmlStreamState{
	InAttributeList, // Stream like <sometag a="b"
	InElement,   // Stream like <sometag a="b" >
};

class XmlWriter;

class XmlElementWriter {
public:
	XmlElementWriter(XmlWriter* root, std::string_view name);
	~XmlElementWriter();
	
	XmlElementWriter makeTag(std::string_view childName);
	void writeAttribute(std::string_view key, std::string_view value);
	void writeText(std::string_view text);
protected:
	void closeAttributeList();
	void closeElement();

    XmlWriter* root = nullptr;
	std::string_view name;
};

class XmlWriter : XmlElementWriter {
public:
	XmlWriter(std::ostream& stream);
	~XmlWriter();
	
private:
    std::ostream& stream;
	XmlStreamState state = XmlStreamState::InElement;
    int depth = 0;
	
	friend XmlElementWriter;
};