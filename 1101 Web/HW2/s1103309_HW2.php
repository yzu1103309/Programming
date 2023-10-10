<?php
$name = $_POST['fullname'];
$ID = $_POST['StudentID'];
$email = $_POST['email'];
$phone = $_POST['phone'];
$department = $_POST['department'];
$gender = $_POST['gender'];
require_once('TCPDF/tcpdf_import.php');
/*-----connect mysql-----*/

$conn = new mysqli('localhost', 'CS380B', 'CS380B','CS380B');
    
if($conn->connect_error){
		die('Connection Failed : '.$conn->connect_error);
	} 
	
$sql = "INSERT INTO s1103309(name, ID, mail, phone, department, gender) VALUES('$name', '$ID', '$email', '$phone', '$department', '$gender')";

$conn->set_charset("utf8");

$conn->query($sql);
	
$conn->close();
	
/*-----end connect-----*/

/*---------------- Create QRcode -----------------*/

include('phpqrcode/qrlib.php');

    $tempDir = "qrcode/";
    
    $codeContents = 'http://140.138.77.70/~s1103309/sign-up/pdf/'.$ID.'.pdf';
    
    $fileName = 'pdf'.$ID.'.png';
    
    $pngAbsoluteFilePath = $tempDir.$fileName;
    $urlRelativeFilePath = $tempDir.$fileName;
    
    if (!file_exists($pngAbsoluteFilePath)) {
        QRcode::png($codeContents, $pngAbsoluteFilePath);
    } 
    
    $codeContents = $ID;
    
    $fileName = 'check-in'.$ID.'.png';
    
    $pngAbsoluteFilePath = $tempDir.$fileName;
    $urlRelativeFilePath = $tempDir.$fileName;
    
    if (!file_exists($pngAbsoluteFilePath)) {
        QRcode::png($codeContents, $pngAbsoluteFilePath);
    } 
/*---------------- End Create -------------------*/

/*---------------- Sent Mail Start -----------------
$charset = 'UTF-8';
$to = $_POST['email'];
$sub = "2021四資迎新報名成功通知及報名表pdf";
$msg = "<h3>狀態：報名成功<br><br>您的姓名：$name<br>您的學號：$ID<br>學系：$department</h3><br>"
."<img src='http://140.138.77.70/~s1103309/sign-up/qrcode/pdf$ID.png' alt='qrcode' />"
."<br><a href='http://140.138.77.70/~s1103309/sign-up/pdf/$ID.pdf'>點我查看報名表</a>";
$headers = "MIME-Version: 1.0\r\n"
."Content-type: text/html; charset=$charset\r\n"
.'From: <2021signup@example.com>'."\r\n";
mail($to,$sub,$msg,$headers); 
---------------- Sent Mail End -------------------*/

/*---------------- Print PDF Start -----------------*/
$pdf = new TCPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);
$pdf->setPrintHeader(false);
$pdf->setPrintFooter(false);
$pdf->SetFont('cid0jp','', 18); 
$pdf->AddPage();


$html = <<<EOF
<style>
table,th,td{
   border:1px solid grey;
}
h2, .center{
  text-align: center;
}
p{
  font-size:12px;
}
</style>
<h2>2021四資迎新報名表</h2>
<table>
<tr>
	<td colspan="2" class="center">就讀系所：$department 一年級</td>
</tr>
<tr>
	<td>姓名：$name</td>
	<td>學號：$ID</td>
</tr>
<tr>
	<td>手機：$phone</td>
	<td>生理性別：$gender</td>
</tr>
<tr>
	<td colspan="2" class="center">Mail：$email</td>
</tr>
</table>
<p>狀態：報名成功</p>
<p>報名表已儲存至：http://140.138.77.70/~s1103309/sign-up/pdf/$ID.pdf
<p>憑報名表繳費。必須遵照防疫規定，活動亦可能因疫情取消</p>
<p></p>
<div class="center"><img src="qrcode/pdf$ID.png"></div>
<div class="center">手機掃描可儲存檔案，已傳送至信箱</div>
<p></p>
<div class="center"><img src="qrcode/check-in$ID.png"></div>
<div class="center">報到用qrcode</div>
EOF;
/*---------------- Print PDF End -------------------*/

$pdf->writeHTML($html);
$pdf->lastPage();
$pdf->Output('/home/s1103309/public_html/sign-up/pdf/'.$ID.'.pdf', 'F');
$pdf->Output('sign-up.pdf', 'I');
