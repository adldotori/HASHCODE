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
