#include "stdafx.h"
#include "WorkInfoCreator.h"

#include <stdio.h>

#include "tinyxml2.h"
#include "stringTransform.h"

using namespace tinyxml2;

WorkInfoCreator::WorkInfoCreator(void)
{
}


WorkInfoCreator::~WorkInfoCreator(void)
{
}

bool WorkInfoCreator::create(task & t)
{
	//�ȼ��������Ϣ
	
	if(t.id <= 0)
		return false;
	if(t.c.id <= 0)
		return false;
	if(t.name.length() <= 0)
		return false;
	if(t.c.name.length() <= 0)
		return false;

	if(
		(t.c.conditions.size() <= 0 || t.c.matchs.size() <= 0) &&
		t.c.link.size() <= 0 &&
		t.c.share.size() <= 0
		)
		return false;
		
	//��ʼ����xml����ʱ������utf8��
	tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();

    XMLDeclaration *declaration = doc->NewDeclaration();
    doc->InsertFirstChild(declaration);

	XMLElement * Commoditys = doc->NewElement("Commoditys");
	XMLNode * root = doc->InsertEndChild(Commoditys);

	XMLElement * Commodity = doc->NewElement("Commodity");
	XMLNode *element = root->InsertEndChild(Commodity);
	Commodity->SetAttribute("id", (int)t.id);

	XMLNode * conditions = element->InsertEndChild(doc->NewElement("SearchCondition"));
	for(int i = 0; i < t.c.conditions.size(); i++)
	{
		XMLElement *sub = doc->NewElement("SubSearchCondition");
		XMLText *text = doc->NewText(t.c.conditions[i].c_str());
		sub->InsertFirstChild(text);
		conditions->InsertEndChild(sub);
	}

	XMLNode * matchs = element->InsertEndChild(doc->NewElement("Match"));
	for(int i = 0; i < t.c.matchs.size(); i++)
	{
		XMLElement *sub = doc->NewElement("SubMatch");
		XMLText *text = doc->NewText(t.c.matchs[i].c_str());
		sub->InsertFirstChild(text);
		matchs->InsertEndChild(sub);
	}

	{
		XMLNode * times = element->InsertEndChild(doc->NewElement("times"));
		CString tmp;
		tmp.Format("%d", 1/*t.times*/); //������ⲻ�������
		XMLText *text = doc->NewText(tmp.GetBuffer(0));
		times->InsertEndChild(text);
	}

	{
		XMLNode * Address = element->InsertEndChild(doc->NewElement("Address"));
		//CString tmp;
		//tmp.Format("%d", 10);
		//XMLText *text = doc->NewText(tmp.GetBuffer(0));
		//Address->InsertEndChild(text);
	}

	{
		XMLNode * Price = element->InsertEndChild(doc->NewElement("Price"));
		//CString tmp;
		//tmp.Format("%d", 10);
		//XMLText *text = doc->NewText(tmp.GetBuffer(0));
		//Price->InsertEndChild(text);
	}

	{
		XMLNode * Postfee = element->InsertEndChild(doc->NewElement("Postfee"));
		//CString tmp;
		//tmp.Format("%d", 10);
		//XMLText *text = doc->NewText(tmp.GetBuffer(0));
		//Postfee->InsertEndChild(text);
	}

	{
		XMLNode * Goon = element->InsertEndChild(doc->NewElement("Goon"));
		CString tmp;
		tmp.Format("%s", "TRUE");
		XMLText *text = doc->NewText(tmp.GetBuffer(0));
		Goon->InsertEndChild(text);
	}

	{
		XMLNode * Share = element->InsertEndChild(doc->NewElement("Share"));
		XMLText *text = doc->NewText(t.c.share.c_str());
		Share->InsertEndChild(text);
	}

	{
		XMLNode * Link = element->InsertEndChild(doc->NewElement("Link"));
		XMLText *text = doc->NewText(t.c.link.c_str());
		Link->InsertEndChild(text);
	}
	//xmlת��ΪUTF8��ʽ���д洢
	XMLPrinter printer;
	doc->Accept(&printer);

	std::string param_string = printer.CStr();
	std::wstring param_wstring;
	string2wstring(param_string, param_wstring);
	std::string param_utf8;
	wstring2utf8string(param_wstring,param_utf8);

	CFile theFile; 
	theFile.Open(_T("./work.xml"),CFile::modeCreate|CFile::modeWrite); 
	theFile.Write((LPCSTR)param_utf8.c_str(),param_utf8.length()); 
	theFile.Close(); 

    delete doc;

	return true;
}
