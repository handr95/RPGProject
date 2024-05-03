# RPGProject :: 머드 게임 만들기

## 작업 목록

### 0401 
1. 맵 크기 입 력시 랜덤맵 생성하기
2. 플레이어 직업 정하는 기능
3. 상하좌우 키보드 버튼 클릭 시 플레이어 이동 가능

### 0408
1. 맵 크기 입력받기
   - 랜덤맵 알고리즘으로 생성하기(플러드필 / BFS / DFS 사용)
2. 빈 타일에 랜덤 몹 생성하여 배치하기
3. 이동후 주변탐색 하여 몹 있는지 체크하기.

### 0415
1. 쓰레드를 활용하여 맵에 생성된 몹 자동으로 이동하는 기능 만들기
   - 공유 자원 사용 시 크리티컬 섹션(윈도우 전용)으로 방지하기

### 0429
1. Critical section RAII 패턴 적용
2. Mob, Player 객체 추상화
3. PlayerManager와 Player 클래스 분리
4. create_map 생성자에서 하지 말고, 원할때 할 수 있도록 기능 분리
5. MapManager Singleton으로 변경

## 참고 자료

- std::cout, printf 차이
  - https://blog.naver.com/view7186/222083168651
- std::system("cls"); 사용시 화면 깜빡거리는 이슈 해결
  - https://blog.naver.com/view7186/222083168651
- 콘솔 색칠
  - https://dev-with-precious-dreams.tistory.com/5
- explicit 키워드 (강제 형변환 안되도록 막는 키워드)
  - https://dydtjr1128.github.io/cpp/2019/07/13/Cpp-explicit-keyowrd.html
- 랜덤맵 생성 시 참고한 알고리즘
  - https://siku314.tistory.com/78
- critical section, mutex, semaphore
