# **File Ninja**
2024 건국대학교 1학기 C프로그래밍 팀 프로젝트 과제로 제출한 결과물입니다.   
본 ReadMe 파일은 실제 제출한 프로젝트 보고서의 내용을 참고하여 작성되었습니다.   

# 문제
교수님께서 제시하신 게임 조건 및 구현 사항에 대한 내용입니다.   

2차원 배열을 이용한 보물찾기 게임을 구현합니다.   

랜덤한 위치에 여러 개의 깃발이 존재하며 이 중 하나의 깃발에는 보물이 숨겨져 있고 나머지 다른 깃발들에서는 보물찾기에 방해가 되는 요소가 등장하거나 보물 위치와 관련된 힌트를 얻을 수 있습니다.   

방향키를 사용하여 플레이어를 조작하며 보물을 찾는 게임을 작성합니다.

### 기본 구현 사항
1. 보물 찾기 게임
   - 깃발을 랜덤하게 배치 후 화면에 출력합니다.
   - 특수 문자나 기호 등을 이용하여 깃발이나 게임 플레이어를 나타냅니다.
   - 방향키를 이용하여 플레이어를 이동시킵니다.
   - 방향키 이동 횟수 또는 플레이 시간에 대한 제약 조건을 두고, 주어진 조건 내에서 보물을 찾으면 사용자가 승리하여 점수를 얻습니다.
   - 벌칙이 주어지거나 보물을 찾는 데에 도움을 주는 깃발을 적어도 하나 이상씩은 배치해야 합니다.
   - 깃발 이외에 다양한 장애물이 존재할 수 있으며 랜덤 함수를 활용하여 매 게임 실행 시마다 깃발이나 장애물의 위치를 달리합니다.
      
2. 레벨 별 난이도 조정
   - 적어도 초급, 중급 및 고급의 세 가지 난이도를 갖는 게임을 제공합니다.
   - 게임 시작 시 난이도를 선택할 수 있습니다.
   - 난이도에 따라 깃발, 장애물 등의 속성을 다르게 설정합니다.
   - 사용자가 선택한 난이도의 게임을 마치면 다음 난이도로 자동으로 이동합니다.
     
### 구현 요구 사항
 - 사용자가 프로그램을 종료할 때까지 반복 수행합니다.
 - 메뉴를 통해서 게임 옵션을 자유롭게 선택할 수 있고 게임을 종료할 수 있습니다.
 - 기호 상수를 적절히 사용하고 배열과 포인터를 활용합니다.
 - 프로그램 기능별로 함수를 생성해서 구현합니다.
     
### 추가 기능 구현
 - 개성 있는 게임 스토리
 - 게임 배경 화면의 구성
 - 벌칙 및 벌점 등의 게임 룰 설정
 - 게임 진행 방법
 - 게임의 재미 요소를 위한 각종 기능 추가

# 게임 소개
플레이어가 정해진 이동 횟수 내에서 주어진 목표 수집물을 전부 모아야 하는 로그라이크 게임입니다.   

### 스토리
플레이어는 컴퓨터 내의 파일 탐색기입니다.   
그는 컴퓨터에 저장된 다양한 파일들로 어지럽혀져 있고 바이러스에 감염된 파일들이 섞여 있는 컴퓨터 속에 있습니다.   
흩어진 데이터를 모두 모아야 해당 난이도의 게임을 탈출할 수 있습니다.   

여기서 장애물은 컴퓨터의 더미 파일로 플레이어가 접근할 수 없는 공간에 해당합니다.   

### 게임 설명
1. 기호

   플레이어는 컴퓨터 내부 공간을 돌아다니며 파일들을 탐색하고 데이터를 수집합니다.
   - 플레이어(*): 방향키를 이용해 조작할 수 있습니다.
   - 방화벽(#): 장애물로써 플레이어는 방화벽을 통과할 수 없습니다.
   - 데이터(@): 바이러스에 감염된 파일일 수도 있고, 탈출하는데 필요한 데이터가 될 수도 있습니다.
    
2. 자원
   
   게임 클리어 시 플레이 시간, 이동 횟수, 미니게임 클리어율을 토대로 등급이 평가됩니다.
   - 플레이 시간 
   - 배터리: 배터리를 모두 소모하면 게임이 끝납니다.
   - 이동 가능 횟수: 플레이어가 방향키를 사용해 이동 가능한 횟수입니다.
   - 방화벽 파괴 가능 횟수: E 키를 사용해 상하좌우 4방향의 방화벽을 파괴할 수 있습니다.
   - 미니게임 클리어율: 전체 미니게임 플레이 횟수에 대한 미니게임 클리어 횟수의 비율입니다.
    
3. 미니게임
   
   데이터를 수집할 때 일정 확률로 미니게임이 실행됩니다.   
   미니게임 성공 시 버프를 얻지만, 실패 시 디버프를 얻게 됩니다.   
    - 똥 피하기: 떨어지는 쓰레기 값들을 피해 유효한 데이터들을 수집해야 합니다.
    - 패스워드: 잠시 보여지는 비밀번호를 기억해 대소문자를 구분하여 정확히 입력해야 합니다.
    - 퀴즈: 컴퓨터공학이나 C프로그래밍과 관련된 간단한 퀴즈를 해결합니다.
    - 틱택토
    - 업다운
    
5. 구성
   
  쉬움, 보통, 어려움 세 가지의 난이도로 구성되어 있습니다.   
  듀토리얼이 존재하며, 스토리모드와 일반 게임 모드로 나뉩니다.

# 개발 
팀 프로젝트로 결과물 제출 및 발표까지 마쳤지만 개인적으로 아쉬운 부분이 있다면 유지 보수가 가능하도록 깃허브에 업로드하였습니다.   
각자 시간날 때 심심풀이 용으로 코드의 수정을 거듭하기를 적극 권장드립니다.   
