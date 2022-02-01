# Một số lưu ý
	Hãy đọc qua phần Bucket trước khi vào phần này 😄 xin cảm ơn 🤎

	Các cấu trúc dữ liệu cây, bảng băm ( của mình ) lưu thông tin gồm một cặp khóa, giá trị ( key, value )
	Vì vậy để lưu trữ, các cây ( của mình ) sẽ thêm, xóa, tìm kiếm một bucket
	💢 Một bucket phải có trạng thái đầy đủ ( isFull ) gồm cả hai khóa thì mới được thêm vào
	💢 Một bucket được trả ra khi tìm kiếm không thấy sẽ có trạng thái không tìm thấy ( notFound ),
		nếu tìm thấy thì bucket sẽ có trạng thái đầy đủ ( isFull ), hãy nhớ kiểm tra điều này tránh nhận phải giá trị rác 😄
	💢 Cần có khóa ( key ) thì mới lấy được giá trị
	💢 Cây sẽ ghi đè giá trị mới vào giá trị cũ nếu khóa bị trùng nhau ( như vậy sẽ không có hai khóa nào bị trùng trong một cây )

# Khai báo
	Khai báo một cây AVL rỗng kiểu int :
		AVLTree<int> tree;

# Các hàm hỗ trợ
	output 	: xem các khóa trong cây ( chỉ xuất khóa )							⏲️ Time complexity : O(n)	👾 Space complexity : O(log n)
	length 	: tính số phần tử ( số nút ) trong cây								⏲️ Time complexity : O(1)
	isEmpty : kiểm tra cây rỗng										⏲️ Time complexity : O(1)
	push 	: nhận vào một bucket để thêm vào cây								⏲️ Time complexity : O(log n)
	pop 	: nhận vào một khóa ( key ) và trả ra một bucket, hàm sẽ xóa nút đó khỏi cây nếu tìm thấy	⏲️ Time complexity : O(log n)
	find 	: nhận vào một khóa ( key ) và trả ra một bucket						⏲️ Time complexity : O(log n)

# Bài tập áp dụng
	📖📖📖 Cho dãy gồm n số nguyên. Đếm số lượng các số đôi một khác nhau trong dãy
	Ví dụ : A { 5, 2, 5, 7, 3, 2, 4 }, n = 7
	Output : 5 phần tử { 2, 3, 4, 5, 7 }
	
	💢 Vì các khóa trên cây không trùng nhau nên số phần tử ( số lượng nút ) trong cây là đáp án. Ở bài này các giá trị ( value ) ta để mặc định là 0
	
	AVLTree<int, int> tree;
	for(int i = 0; i < n; i++)
		tree.push(bucket<int, int>(rand(), 0));
	printf("Output : %d", tree.length());
	//⏲️ Time complexity : O(n log(n))
	
	📖📖📖 Áp dụng cho các bài toán quản lý từ vựng Anh - Việt, quản lý sinh viên gồm (mã sinh viên, sinh viên), ...

# Giới thiệu các hàm xử lý trên cây AVL
	Thực hành trên : https://www.cs.usfca.edu/~galles/visualization/AVLtree.html

	- Lớp node trong cây :
		+ Các hàm hỗ trợ :
			countHeight : tính lại chiều cao của nút đó ( nút thực hiện tính lại chiều cao sau khi quay )
			copyBucket : sao chép giá trị của một bucket vào thành viên info của nó
			countTilt : tính độ nghiêng giữa hai cây con trái và phải ( left->height - right->height )
		
		+ Các hàm tĩnh :
			rotateLeft, rotateRight : quay trái, quay phải
			balanceRoot : kiểm tra độ lệch giữa hai cây con ( countTilt )
				Nếu nghiêng trái : kiểm tra cây con trái có bị nghiêng phải
				Nếu nghiêng phải : kiểm tra cây con phải có bị nghiêng phải
				thực hiện quay tại nút đó theo quy tắc của cây AVL
				
			poorChildLeft, poorChildRight : dùng trong trường hợp xóa nút
				từ nút mang khóa đã tìm thấy ( nút này có hai cây con ),
				hàm sẽ tìm nút thế mạng, sao chép bucket và xóa,
				thực hiện cân bằng từ nút cha của nút thế mạng trở lên nút root
				
	- Lớp AVL Tree :
		+ Các hàm tĩnh :
			pushRecursive		: thêm một bucket sử dụng đệ quy và tự cân bằng lại
			popRecursive		: xóa một bucket sử dụng đệ quy và tự cân bằng lại
			outputRecursiveLNR	: hàm đệ quy xuất cây theo thứ tự Left Node Right
			clear			: hàm đệ quy giải phóng tất cả nút trong cây
