# Hướng dẫn sử dụng Queue 💻
	Khai báo
	Các hàm hỗ trợ
	Các toán tử

# Khai báo 
	Khởi tạo một hàng đợi rỗng kiểu int :
		queue<int> qu;
	Khởi tạo sao chép một hàng đợi cũ cùng kiểu :
		queue<int> qu2(qu);
		
# Các hàm hỗ trợ
	output 		: xem hàng đợi										⏲️ Time complexity : O(n)
	isEmpty 	: kiểm tra hàng đợi rỗng								⏲️ Time complexity : O(1)
	length 		: tính số phần tử trong hàng đợi							⏲️ Time complexity : O(1)
	get 		: xem giá trị ở đỉnh hàng đợi								⏲️ Time complexity : O(1)
	swap 		: hoán vị hai hàng đợi									⏲️ Time complexity : O(1)
	push 		: thêm một phần tử vào hàng đợi								⏲️ Time complexity : O(1)
	pop 		: lấy ra một phần tử trong hàng đợi							⏲️ Time complexity : O(1)
	isFound	 	: có tồn tại một giá trị nào trong hàng đợi						⏲️ Time complexity : O(n)
	
# Các toán tử
	operator= 	: sao chép các giá trị từ một hàng đợi khác						⏲️ Time complexity : O(n)
