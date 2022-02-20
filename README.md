## Timeline

~ :30 : 문제 이해, I/O 구현, evaluation code 구현

~ :45 : 테스트 케이스 분석

~ 1:30 : greedy

~ 2:30 : research

~ 4:00 : solution!

- 시간 대략적으로 계산해보고 테스트해보기
- 테스트 케이스 분석해보기

# 2022_practice_round

> goal [d: 1805, e: 2052]

## constraints

|             | a   | b   | c   | d    | e     |
| ----------- | --- | --- | --- | ---- | ----- |
| clients     | 3   | 5   | 10  | 9368 | 4986  |
| ingredients | 6   | 6   | 10  | 600  | 10000 |

## experiment

|                     | a   | b   | c   | d    | e       | description                                                                                                                                                                                                                               |
| ------------------- | --- | --- | --- | ---- | ------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| moooooooojisung.cpp | 2   | 5   | 4   | 1697 | 799     | good - bad > 0                                                                                                                                                                                                                            |
| mooooooojisung.cpp  | 2   | 5   | 4   | 1748 | 834     | 안좋은 거 30개 빼고 좋은 거 30개 더하기                                                                                                                                                                                                   |
| moooooojisung.cpp   | 2   | 5   | 5   | 1726 | timeout | beam search (beam=5, count=10)                                                                                                                                                                                                            |
| youjisung.cpp       | 2   | 5   | 4   | 1596 | 1920    | 그래프 (vertex: client, edge: 한 클라이언트는 좋아하고 한 클라이언트는 싫어하는 재료가 있는 경우) 문제로 변환. 엣지가 없는 최대 정점 그래프 찾는 문제! [https://codeforces.com/blog/entry/99020](https://codeforces.com/blog/entry/99020) |
| yooujisung.cpp      | 2   | 5   | 5   | 1708 | 2025    | 정점 삭제할 때 degree 하나씩 낮추기, degree 0으로 시작                                                                                                                                                                                    |
| yoooujisung.cpp     | 2   | 5   | 5   | 1784 | 2025    | yooujisung + moooooojisung                                                                                                                                                                                                                |
| yooooujisung.cu     | 2   | 5   | 5   | 1788 | 2025    | with cuda                                                                                                                                                                                                                                 |

# 2021_qual_round

> goal : 9,754,280

## constraints

|     | a   | b    | c     | d     | e    | f     |
| --- | --- | ---- | ----- | ----- | ---- | ----- |
| I   | 4   | 7073 | 10000 | 8000  | 500  | 1662  |
| S   | 5   | 9102 | 35030 | 95928 | 998  | 10000 |
| V   | 2   | 1000 | 1000  | 1000  | 1000 | 1000  |

## experiment

|                 | a    | b       | c       | d       | e      | f       | description               |
| --------------- | ---- | ------- | ------- | ------- | ------ | ------- | ------------------------- |
| Maximum Score   | 1002 | 4575980 | 1328384 | 3986579 | 920385 | 1765039 | 모든 신호등이 초록불일 때 |
| moooojisung.cpp | 1002 | 4567157 | 1230757 | 1092420 | 870018 | 1402872 | all streets are fair      |
