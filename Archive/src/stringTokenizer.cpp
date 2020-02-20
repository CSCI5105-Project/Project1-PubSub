#include "stringTokenizer.h"
#include <iostream>

using namespace std;

int CStringTokenizer::GetSize()
{
	return m_tokenList.size();
}

bool CStringTokenizer::HasMoreTokens()
{
	return m_index != m_tokenList.end();
}

string CStringTokenizer::GetNext()
{
	if(m_index!= m_tokenList.end()) 
	{
		return *(m_index++);
	}
	else
	{
		return "";
	}
}

string CStringTokenizer::GetCurrent()
{
	if(m_index!= m_tokenList.end())
	{
		return *(m_index);
	}
	else
	{
		return "";
	}
}

void CStringTokenizer::Split(const string strInput, const string strDelimiter)
{
	//Empty Previous tokens.
	m_tokenList.clear();
	string::size_type pos = strInput.find_first_of(strDelimiter, 0); //Find the seperator
	string::size_type lastPos = 0; //Find the not seperator

	string strToken;

	while(string::npos != pos || string::npos!=lastPos)
	{
		strToken = strInput.substr(lastPos, pos-lastPos);

		m_tokenList.push_back(strToken);

        if ((pos != string::npos) && (strInput[pos+1] == strDelimiter[0])) {
            lastPos = ++pos;
        } else {
            lastPos = strInput.find_first_not_of(strDelimiter, pos); //Find again
            pos = strInput.find_first_of(strDelimiter, lastPos); //Find again
        }
		// cout << lastPos << " " << pos << endl << flush;
	}

	m_index = m_tokenList.begin();
}
