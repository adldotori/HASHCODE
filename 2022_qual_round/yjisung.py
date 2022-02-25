contributors = {}
projects = {}
project_order = []
skill_to_contributors = {}

D = {}
S = {}
B = {}

if __name__ == "__main__":
    input_file = "in/f.txt"

    # Read the input file
    with open(input_file, "r") as f:
        c, p = list(map(int, f.readline().strip().split(" ")))
        for _ in range(c):
            name, skillcnt = f.readline().strip().split(" ")
            skills = {}
            for _ in range(int(skillcnt)):
                skill, level = f.readline().strip().split(" ")
                skills[skill] = int(level)
                skill_to_contributors.setdefault(skill, []).append([name, int(level)])
            contributors[name] = {"skill": skills}
        for _ in range(p):
            name, d, s, b, r = f.readline().strip().split(" ")
            D[name] = int(d)
            S[name] = int(s)
            B[name] = int(b)
            skills = []
            for _ in range(int(r)):
                skill, level = f.readline().strip().split(" ")
                skills.append([skill, int(level)])
            projects[name] = skills

result = []
already_done = []
while True:
    keys = []
    for key, value in projects.items():
        if key in already_done:
            continue
        d = {}
        for skill, level in value:
            if skill not in d:
                d[skill] = [level]
            else:
                d[skill].append(level)

        success = True
        for skill, levels in d.items():
            levels = sorted(levels, reverse=True)
            cnt = len(levels)
            hubo_list = sorted(
                skill_to_contributors[skill], key=lambda x: x[1], reverse=True
            )[:cnt]
            if len(hubo_list) < cnt:
                success = False
                break

            for a, b in zip(levels, hubo_list):
                if a > b[1]:
                    success = False
                    break
        if success:
            keys.append(key)
    if len(keys) == 0:
        break
    already_done += keys
    for p in keys:
        index = [i[0] for i in sorted(enumerate(projects[p]), key=lambda x: x[1][1])]
        skilllist = sorted(projects[p], key=lambda x: x[1])
        member = [""] * len(skilllist)

        for idx, (skill, level) in zip(index, skilllist):
            hubo = sorted(skill_to_contributors[skill], key=lambda x: x[1])
            for name, lv in hubo:
                if lv < level:
                    continue
                if name in member:
                    continue
                elif lv == level:
                    member[idx] = name
                    skill_to_contributors[skill].remove([name, lv])
                    skill_to_contributors[skill].append([name, lv + 1])
                    break
                else:
                    member[idx] = name
                    break
        for x in f:
            if x == "":
                print("WRONG")
        result.append([p] + member)

with open("out/yjisung.txt", "w") as f:
    f.write(str(len(result)) + "\n")
    for res in result:
        f.write(res[0] + "\n")
        f.write(" ".join(res[1:]) + "\n")
