# https://blog.csdn.net/fur_pikachu/article/details/126357482?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-126357482-blog-133655876.235%5Ev40%5Epc_relevant_3m_sort_dl_base3&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-126357482-blog-133655876.235%5Ev40%5Epc_relevant_3m_sort_dl_base3&utm_relevant_index=1
# http://www.jsons.cn/unicode/

f = open("data.txt", "r")

st = []

for line in f:
    strs = line.split(',')

    for s in strs:
        if s not in st:
            st.append(s)

for s in st:
    print(s + ", ", end = "")
