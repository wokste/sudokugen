#include "XmlWriter.h"
#include <iostream>
#include <cassert>
#include <string_view>

XmlElementWriter::XmlElementWriter(XmlWriter* root, std::string_view name) : root(root), name(name) {
	if (root == nullptr)
		return; // This is the root. Construction will happen in the parent.
	
	root->depth++;
}

XmlElementWriter::~XmlElementWriter() {
	if (root == nullptr)
		return; // This is the root. Destruction has already happened in the child.
	
	closeElement();
	root->depth--;
}

XmlElementWriter XmlElementWriter::makeTag(std::string_view childName){
	closeAttributeList();
	
	root->state = XmlStreamState::InAttributeList;
	root->stream << "<" << childName;
	return XmlElementWriter(root, childName);
}

void XmlElementWriter::writeAttribute(std::string_view key, std::string_view value){
	assert(root->state == XmlStreamState::InAttributeList);
	
	root->stream << " " << key << "=\"" << value << "\"";
}

void XmlElementWriter::writeText(std::string_view text){
	closeAttributeList();
	root->stream << text;
}

void XmlElementWriter::closeAttributeList(){
	switch (root->state)
	{
		case XmlStreamState::InAttributeList:
			root->stream << ">";
			break;
		case XmlStreamState::InElement:
			break; // nothing left to do.
		default:
			assert(false); // undefined enum value.
			break;
	}
	root->state = XmlStreamState::InElement;
}

void XmlElementWriter::closeElement(){
	switch (root->state)
	{
		case XmlStreamState::InAttributeList:
			root->stream << "/>";
			break;
		case XmlStreamState::InElement:
			root->stream << "</" << name << ">";
			break;
		default:
			assert(false); // undefined enum value.
			break;
	}
}


XmlWriter::XmlWriter(std::ostream& stream) : XmlElementWriter(nullptr, ""), stream(stream) {
	root = this;
}

XmlWriter::~XmlWriter(){
	root = nullptr;
	assert(depth == 0);
}