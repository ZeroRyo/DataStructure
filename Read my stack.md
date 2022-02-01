# Hướng dẫn sử dụng Stack 💻
	Khai báo
	Các hàm hỗ trợ
	Các toán tử

# Khai báo 
	Khởi tạo một ngăn xếp rỗng kiểu int :
		stack<int> st;
	Khởi tạo sao chép một ngăn xếp cũ cùng kiểu :
		stack<int> st2(st);
		
# Các hàm hỗ trợ
	tput 		: xem ngăn xếp										⏲️ Time complexity : O(n)
	isEmpty 	: kiểm tra ngăn xếp rỗng								⏲️ Time complexity : O(1)
	length 		: tính số phần tử trong ngăn xếp							⏲️ Time complexity : O(1)
	get 		: xem giá trị ở đỉnh ngăn xếp								⏲️ Time complexity : O(1)
	swap 		: hoán vị hai ngăn xếp									⏲️ Time complexity : O(1)
	push 		: thêm một phần tử vào ngăn xếp								⏲️ Time complexity : O(1)
	pop 		: lấy ra một phần tử trong ngăn xếp							⏲️ Time complexity : O(1)
	isFound	 	: có tồn tại một giá trị nào trong ngăn xếp						⏲️ Time complexity : O(n)
	
# Các toán tử :
	operator= 	: sao chép các giá trị từ một ngăn xếp khác						⏲️ Time complexity : O(n)
