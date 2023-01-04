## ToDoList

- [x] 규칙 정하기
- [x] 코드 컨벤션 정하기
- [x] 깃 메세지 컨벤션 정하기
- [x] Makefile 기초 적인 거 수정 (libft 컴파일 추가 등)
- [x] 요구사항 파악하기
	- pdf 확인하기
	- 필요한 지식 파악하기

<details>
<summary>map parsing</summary>

- [x] map parsing
	- [x] 파일 .cub로 끝나는 지 확인
	- [x] 파일 열고 open 예외처리
	- [x] 파일 다 읽어오기
	- [x] 텍스저 저장
		- [x] 중복 처리
		- [x] 개수 처리
		- [x] 텍스처 파일이 있는지
			- [x] mlx_xpm_to_image 함수 사용하기
			- [x] 예외 처리 하기
		- [x] 텍스처 파일 이름 저장
	- [x] 맵 저장
		- [x] 맵 패딩
		- [x] 맵 유효성 체크
    		- [x] 중간에 이상한 값
    		- [x] 중간에 개행
    		- [x] 벽이 뚫려있음 (0의 벡터에 ' '가 있을 경우)
		- [x] 플레이어 정보
	- [x] 릭 체크하기
    - [x] error 처리하기
        - [x] 테스터기 돌려보기
        - [x] error message 수정
</details>

<details>
<summary>render</summary>

- [ ] mlx
	- [x] mlx init
	- [x] new window
	- [x] texture.xpm 파일 추가
	- [x] mlx put img
		- destroy 하고, 새로 init 해주고
- [ ] ray casting
	- [ ] wall
		- [ ] 처음 방향 설정
		- [x] hit 지점 찾기
		- [x] 이미지 버퍼에 텍스처 담기
		- [x] 화면 프린트
		- [x] 방향 바뀌는 거
			- [x] 회전 행렬 공식 갖다 쓰기
	- [x] floor & ceiling
		- [x] 바닥과 천장 칠하기

</details>

- [x] key hook
	- [x] 플레이어 이동

- [ ] norminette
- [ ] 함수 자르기 및 이름 수정
### 1229 목표

- [x]  ray casting 방식
	- [x] 최소한의 이해
