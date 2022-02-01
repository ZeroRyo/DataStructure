# Giới thiệu Bucket 📑
	Các cấu trúc dữ liệu cây cần thông qua các phép so sánh trên một khóa ( key ) để tìm kiếm, thêm và xóa đạt hiệu quả tốt nhất
	Vì thế một nút trên cây gồm hai thành phần : khóa ( key ) và giá trị ( value )
	Bucket ( của mình ) được thiết kế cho việc sử dụng trên cây như thêm, xóa, tìm kiếm một cặp (khóa, giá trị)
	Vì thế một bucket ( của mình ) bao gồm cả hai thành phần : khóa ( key ) và giá trị ( value )
	Các cấu trúc dữ liệu cây, bảng băm ( của mình ) phải khai báo thư viên này
	
	🖌️ Bucket ( của mình ) có bốn trạng thái :
		▶️ Đầy đủ 		( isFull )	: khi nó có đủ hai thành phần gồm khóa ( key ) và giá trị ( value )
		▶️ Rỗng 		( isEmpty )	: khi nó không có gì cả
		▶️ Không có giá trị 	( notValue )	: khi nó chỉ có khóa ( key ) mà không có giá trị ( value )
		▶️ Không tìm thấy 	( notFound ) 	: khi một cây trả về một bucket mà trước đó nó không tìm thấy một khóa được chỉ định
		
# Giới thiệu Status 📑
	Status ( của mình ) dùng enum class gồm bốn thành viên : isFull, isEmpty, notValue, notFound
	
# Khai báo
	Khai báo một bucket đầy đủ :
		bucket<int, int> buck(1, 2);
		bucket<string, int> buck("abc", 2);
		bucket<string, string> buck("cat", "meo");
		
	Khai báo một bucket rỗng :
		bucket<int, int> buck;
		bucket<string, int> buck;
		bucket<string, string> buck;
		
	Khai báo một bucket không có giá trị : 
		bucket<int, int> buck(1);
		bucket<string, int> buck("abc");
		bucket<string, string> buck("cat");
		
	Khai báo một bucket có trạng thái "notFound" : các cây tìm kiếm sẽ trả về nó khi không tìm thấy
		bucket<int, int> buck(status::notFound);
		
	Khai báo một bucket được sao chép từ bucket cũ :
		bucket<int, int> buck2(buck);
		
# Các hàm hỗ trợ
	getKey 		: trả về khóa ( key ) nó đang giữ
	getValue 	: trả về giá trị ( value ) nó đang giữ
	getStatus 	: trả về trạng thái của bucket
	change 		: thay đổi bucket
	isEmpty 	: kiểm tra trạng thái của bucket có phải là rỗng
	isFull 		: kiểm tra trạng thái của bucket có phải là đầy đủ
	notValue 	: kiểm tra trạng thái của bucket có phải là thiếu giá trị
	notFound 	: kiểm tra trạng thái của bucket có phải là không tìm thấy
	
# Các toán tử
	operator> , operator== , operator<	: so sánh hai bucket dựa vào khóa ( key ) của chúng
