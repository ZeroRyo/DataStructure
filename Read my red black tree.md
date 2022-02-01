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
	Khai báo một cây đỏ đen rỗng có khóa kiểu int, giá trị kiểu int :
		RBTree<int, int> tree;

# Các hàm hỗ trợ
	output 	: xem các khóa trong cây ( chỉ xuất khóa ), ký tự ']' là nút đen, ')' là nút đỏ			⏲️ Time complexity : O(n)	👾 Space complexity : O(log n)
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
	//Hãy so sánh thời gian thực thi giữa hai cây AVL và cây đỏ đen với n = 1.000.000.000
	
	RBTree<int, int> tree;
	for(int i = 0; i < n; i++)
		tree.push(bucket<int, int>(rand(), 0));
	printf("Output : %d", tree.length());
	//⏲️ Time complexity : O(n log(n))
	
	📖📖📖 Áp dụng cho các bài toán quản lý từ vựng Anh - Việt, quản lý sinh viên gồm (mã sinh viên, sinh viên), ...

# Giới thiệu các hàm xử lý trên cây đỏ đen
	Tìm hiểu 5 tính chất, 5 trường hợp thêm và 6 trường hợp xóa trên cây đỏ đen
	Code được tham khảo trên : https://vi.wikipedia.org/wiki/C%C3%A2y_%C4%91%E1%BB%8F_%C4%91en
	
	- Lớp node trong cây :
		+ Các hàm hỗ trợ :
			connectLeft, connectRight		: nối với cây con trái, phải
			rotateLeft, rotateRight			: xoay trái, phải
			isBlack, isRed				: kiểm tra màu của nút ( có thể nhận vào một nullptr )
			uncle, sibling				: trả về địa chỉ nút chú, nút anh
			refSibling, refParent, refGrandParent	: trả về một tham chiếu con trỏ của nút anh, cha, ông
			insertCase1...5				: 5 trường hợp thêm
			deleteCase1...6				: 6 trường hợp xóa
			deleteNode				: xóa nút lá hoặc nút chỉ có một con
			findPoorLeftChild			: xóa nút có hai con
		
		+ Các hàm tĩnh :
			
				
	- Lớp RB Tree :
		+ Các hàm tĩnh :
			outputRecursiveLNR			: hàm đệ quy xuất cây theo thứ tự Left Node Right
			clear					: hàm đệ quy hủy tất cả các nút trên cây
