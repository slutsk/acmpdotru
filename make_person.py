import requests
import chardet
import re
user_name = ['* V A', '* Гр Кл', '* Гч Кл', '* См Дл',  '* Пч Дд', '* Ач Ер', '* Да Пр', '* Во Гб', '* Sn Pa', '* Кй Нй', '* Хв Мй', '* Бч Ай', 'Кк Мм']
user_id   = [  92960,    463065,    488679,    486774,     529387,    467234,    530286,    435953, 541052, 546179, 549344,           550727, 550729]
numbers   = []
for ind in range(len(user_name)):
    url = "https://acmp.ru/index.asp?main=user&id="+str(user_id[ind])  # Замените на нужный URL
           
    response = requests.get(url)
    
    if response.status_code == 200:
        detected_encoding = chardet.detect(response.content)['encoding']
        
        if detected_encoding.lower() != 'windows-1251':
            content = response.content.decode(detected_encoding).encode('windows-1251')
        else:
            content = response.content
    
        with open("output.html", "wb") as file:
            file.write(content)
    
        print("HTML-код страницы успешно сохранен в файл output.html с учетом кодировки windows-1251")
    else:
        print(f"Не удалось загрузить страницу, статус-код: {response.status_code}")


# Читаем содержимое HTML-файла
    with open("output.html", "r", encoding='windows-1251') as file:
        lines = file.readlines()
    
    numbers.append(user_name[ind]+'\n');
    
    # Поиск строк с текстом "<b class=btext>Решенные задачи (число):</b>"
    pattern = re.compile(r'<b class=btext>Решенные задачи \(\d+\):</b>')
    
    for i in range(len(lines)):
        if pattern.search(lines[i]):
            if i + 1 < len(lines):  # Проверяем, что следующая строка существует
                next_line = lines[i + 1]
                numbers_in_line = re.findall(r'>(\d+)<', next_line)
                numbers.extend(numbers_in_line)
    numbers.append('\n');
    
# Записываем числа в текстовый файл
with open("person.txt", "w", encoding='utf-8') as file:
    file.write(' '.join(numbers))

print(f"Числа из строк, следующих за шаблоном <b class=btext>Решенные задачи (число):</b>, успешно сохранены в файл numbers.txt")






