/*
 * Created on September 21, 2018, 4:19 PM */
#include <iostream>
#include <string>
#include <fstream>

//===================================================================================
class DynamicArray 
{
private:
    std::string *m_array;
    int m_size;

public:
    DynamicArray()
    {
        m_size = 0;
        m_array = nullptr;
    }

    ~DynamicArray()
    {
        if(m_array != nullptr)
            delete[] m_array;
        m_array = nullptr;
    }

    int getSize(){return m_size;}
    
    //array bound check
    std::string &operator[] (int i)
    {
        if(i >= 0 && i < m_size)
            return m_array[i];
    }

    //add a new string to array
    void add(const std::string &str)
    {
        bool found = false;
        for(int i = 0; i < m_size; ++i)
        {
            //check if new string is found in the string array
            if(m_array[i] == str)
            {
                found = true;
                break;
            }
        }
        //if new string is not found then add string to array
        if(!found)
        {
            ++m_size;
            std::string *temp = new std::string[m_size];
            if(m_array != nullptr)
            {
                for(int i = 0; i < m_size-1; ++i)
                    temp[i] = m_array[i];

                delete[] m_array;
            }
            m_array = temp;
            m_array[m_size - 1] = str; 
        }
    }
    void display()
    {
        for(int i = 0; i < m_size; ++i)
        {
            std::cout << m_array[i];
            if(i < m_size-1)    //for last element, dont display *
                std::cout << "*";
        }
    }
    
    void sequence(const std::string &str1, const std::string &str2)
    {   
        //if length of any string is 0 than end comparing
        if(str1.length() == 0 || str2.length() == 0)
            return;
        
        int i1 = 0;
        int i2 = 0;
        
        //move forward index by index in string1 until the characters are same
        while(str2[i2] != str1[i1])
        {
            ++i1;
            if(str1[i1] == '\0')
                return;
        }
        int tempSize = 0;
        //calculate the size of sub string which is similar
        while(str1[i1 + tempSize] == str2[i2 + tempSize])
        {
            ++tempSize;
            //if both string index are at end than end comparing 
            if(str1[i1 + tempSize] == '\0' && str2[i2 + tempSize] == '\0')
                break;
        }
        
        //save the similar substring in a new string variable
        std::string tempStr = str2.substr(i2, tempSize);
        int tempSizeOld = tempSize;
        
        int i1_3 = i1;
        //if last similar character of str1 IS NOT same as the next one
        if(str1[i1 + tempSize] != str1[i1 + tempSize - 1])
        {
            //find the similar string in str1 and save the start index in a variable
            int i1_2 = str1.find(tempStr, i1 + tempSize);

            //do the following until you cant find any more string which is similar
            while(i1_2 != std::string::npos)
            {
                int tempSize_2 = tempSize;
                //calculate the size of the new string
                while(str1[i1_2 + tempSize_2] == str2[i2 + tempSize_2])
                {
                    ++tempSize_2;
                    if(str1[i1_2 + tempSize_2] == '\0' && str2[i2 + tempSize_2] == '\0')
                        break;
                }
					//if size of new string is greater than size of new string, than save the new string
	                if(tempSize_2 > tempSize)
	                {
	                    tempSize = tempSize_2;
	                    tempStr = str2.substr(i2, tempSize);
	                    i1_3 = i1_2;
	                }    
	                //find the very next similar string in str1 and update the index variable
	                i1_2 = str1.find(tempStr, i1_2 + tempSize);
            }
            
    		//if last similar character of str1 IS same as the next one, then put * and send substring
            if(str1[i1_3 + tempSize] == str1[i1_3 + tempSize - 1])
            {
            	tempStr = str2.substr(i2, tempSize);
				add(tempStr);
				sequence(str1.substr(i1_3+tempSize), str2.substr(i2+tempSize));
				return;
			}
            add(tempStr);
        }
        else
        {
            //check if the new string to be added has previously been saved or not
            add(tempStr);

            //Send substring recursively, after removing the similar part and everything before that
            sequence(str1.substr(i1+tempSize), str2.substr(i2+tempSize));
        }
    }
};

//===================================================================================
int main()
{
    std::string str1;
    std::string str2;
    
    //read data from file Named "Input.txt"
    std::ifstream inf("Input.txt");
    if(!inf)
    {
        std::cout << "Cannot open File.\n";
        exit(1);
    }
    inf >> str1;
    inf >> str2;
    std::cout << str1 << "\n";
    std::cout << str2 << "\n";
    
    DynamicArray da;
    da.sequence(str1, str2);
    da.display();
    
    return 0;
}

//===================================================================================
