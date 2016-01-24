#include "stdafx.h"
#include "WorkInfoCreator.h"

#include <stdio.h>

#include "tinyxml2.h"

using namespace tinyxml2;

WorkInfoCreator::WorkInfoCreator(void)
{
}


WorkInfoCreator::~WorkInfoCreator(void)
{
}


bool WorkInfoCreator::create(task & t)
{
	tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();

    // use the standard declaration by default
    XMLDeclaration *declaration = doc->NewDeclaration();
    doc->InsertFirstChild(declaration);

    // insert 'element' node
    XMLNode *element = doc->InsertEndChild(doc->NewElement("element"));

    // insert 'sub' nodes
    XMLElement *subs[5];
	char des[5][20] = 
	{
		"random",
		"times",
		"times_1",
		"times_2",
		"times_3"
	};

	XMLNode * conditions = element->InsertEndChild(doc->NewElement("conditions"));
	for(int i = 0; i < 3; i++)
	{
		XMLElement *sub = doc->NewElement("subcondition");
		XMLText *text = doc->NewText("conditions......");
		sub->InsertFirstChild(text);
		conditions->InsertEndChild(sub);
	}

	XMLNode * matchs = element->InsertEndChild(doc->NewElement("matchs"));
	for(int i = 0; i < 3; i++)
	{
		XMLElement *sub = doc->NewElement("submatch");
		XMLText *text = doc->NewText("match......");
		sub->InsertFirstChild(text);
		matchs->InsertEndChild(sub);
	}

	XMLElement *random = doc->NewElement("random");
	random->SetAttribute("value", 1);
	element->InsertEndChild(random);

	XMLElement *times = doc->NewElement("times");
	times->SetAttribute("value", 2);
	element->InsertEndChild(times);

	XMLElement *times_1 = doc->NewElement("times_1");
	times_1->SetAttribute("value", 2);
	element->InsertEndChild(times_1);

	XMLElement *times_2 = doc->NewElement("times_2");
	times_2->SetAttribute("value", 2);
	element->InsertEndChild(times_2);

	XMLElement *times_3 = doc->NewElement("times_3");
	times_3->SetAttribute("value", 2);
	element->InsertEndChild(times_3);


	/*
    for (int i = 0; i < 7; ++i) {
        XMLElement *sub = doc->NewElement(des[i]);
        //sub->SetAttribute("attr", i+1);
        element->InsertEndChild(sub);
        subs[i] = sub;
    }*/

    // insert text to 3rd 'sub' node
 //   XMLText *text = doc->NewText("& Text!");
    // text->SetCData(true);  // <![CDATA[& Text!]]>
 //   subs[2]->InsertFirstChild(text);


    // save xml, true for compact
    XMLError error = doc->SaveFile("./work.xml", true);

    delete doc;

	return false;
}
