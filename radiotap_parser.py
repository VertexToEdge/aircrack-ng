import requests
from bs4 import BeautifulSoup
from bs4.element import Comment

radiotap_fields = "http://www.radiotap.org/fields/defined"
radiotap_sugested_fields = "https://www.radiotap.org/fields/suggested"

res = requests.get(radiotap_fields)
soup = BeautifulSoup(res.text,"html.parser")
all_link = soup.select("div ul li a")

res = requests.get(radiotap_sugested_fields)
soup = BeautifulSoup(res.text,"html.parser")
all_suggest_link = soup.select("div ul li a")

def analyzeField(url):
    print(url)
    res = requests.get("http://www.radiotap.org" + url)
    soup = BeautifulSoup(res.text,"html.parser")

    def tag_visible(element):
        if element.parent.name in ['style', 'script', 'head', 'title', 'meta', '[document]']:
            return False
        if isinstance(element, Comment):
            return False
        if str(element) == "\n":
            return False
        return True
    texts = soup.findAll(text=True)
    texts =[i.strip() for i in filter(tag_visible, texts)]
    name = texts.index("rejected fields") +1
    id = texts.index("Bit Number") +1
    type =  texts.index("Structure") +1

    texts[id] = texts[id].split(" ")

    for i in texts[id]:
        if i.isdigit():
            texts[id] = i
            break
    return [texts[id],texts[name],texts[type]]

result = []
for i in all_link:
    result.append(analyzeField(i['href']))
for i in all_suggest_link:
    result.append(analyzeField(i['href']))


#result = sorted(result,key=lambda key:key[0])
result.sort(key=lambda i: int(i[0]))
print(result)

def nameConvert(str):
    return str.lower().replace("-","_").replace(" ","_").replace("/","_").replace("0","zero")
def typeConvert(str):
    if str[0] == "u":
        return str.replace("u","uint") + "_t"
    if str[0] == "s":
        return str.replace("s", "int") + "_t"
def makeStruct(element):
    struct_name = nameConvert(element[1])
    type = element[2].split(",")

    struct_member = []
    last_type = ""
    type_list = ["u8","u16","u32","u64","s8","s16","s32"]

    if len(type) == 1 and type[0].strip() in type_list:
        return "typedef %s %s;\n"%(typeConvert(type[0].strip()), struct_name)
    else:
        for i in type:
            i=i.strip().replace("\n"," ").split(" ")
            if i[0] in type_list:
                if len(i) == 1:
                    last_type = typeConvert(i[0])
                    struct_member.append("\t%s %s;" % (last_type, "unknown"))
                else:
                    last_type = typeConvert(i[0])
                    struct_member.append("\t%s %s;"%(last_type,nameConvert("_".join(i[1:]))))
            else:
                struct_member.append("\t%s %s;"%(last_type,nameConvert("_".join(i))))

    result = "struct %s{\n"%(struct_name)
    result += "\n".join(struct_member)
    result += "\n};\n"
    return result
def makeEnum(element):
    result = "enum RADIOTAP_FIELD{\n"
    for i in element:
        result += "\t%s=%s,\n"%(nameConvert(i[1]).upper(),i[0])
    result += "}\n"
    return result
def makeCondition(elements):
    result = ""
    for i in elements:
        result += "if(i==%s){\n"%(nameConvert(i[1]).upper())
        result += "\t%s b;\n"%(nameConvert(i[1]))
        result += "\tmemcpy(&b,data,sizeof(%s));\n"%(nameConvert(i[1]))
        result += "\telements[i]=b;\n"
        result += "\tdata += sizeof(%s);\n"%(nameConvert(i[1]))
        result += "}\nelse "
    result[:-5]
    return result

struct_list = "\n".join([makeStruct(i) for i in result])

#print(struct_list)
#print(makeEnum(result))

print(makeCondition(result))