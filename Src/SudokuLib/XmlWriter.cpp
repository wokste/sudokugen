#include <cassert>
#include <iostream>
#include <string_view>

#include "XmlWriter.h"

using namespace std;

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

void XmlElementWriter::set(std::string_view key, std::string_view value){
	assert(root->state == XmlStreamState::InAttributeList);
	
	root->stream << " " << key << "=\"" << value << "\"";
}

void XmlElementWriter::set(std::string_view key, double value) {
	assert(root->state == XmlStreamState::InAttributeList);

	root->stream << " " << key << "=\"" << value << "\"";
}

void XmlElementWriter::setText(std::string_view text){
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
	root->state = XmlStreamState::InElement;
}


XmlWriter::XmlWriter(std::ostream& stream) : XmlElementWriter(nullptr, ""), stream(stream) {
	assert(stream.good());
	root = this;
}

XmlWriter::~XmlWriter(){
	root = nullptr;
	assert(depth == 0);
}