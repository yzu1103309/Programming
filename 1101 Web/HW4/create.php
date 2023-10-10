<?php
$Email = $_POST['Email'];
$Password = strval($_POST['password']);
$Password2 = strval($_POST['password2']);
$Name = $_POST['name'];

/*-----connect mysql-----*/

$conn = new mysqli('localhost', 'root', 'MushroomDawn','ToDoList');
$sql = "SELECT `Email` FROM `users` WHERE `Email` LIKE '".$Email."'";
    
if($conn->connect_error){
    die('Connection Failed : '.$conn->connect_error);
}else if(!( $result = mysqli_query($conn,$sql))){
    print("query error.");
}else if(empty($Name)){
    print("Name can't be empty.");
}else if(empty($Email)){
    print("Email can't be empty");
}else if(empty($Password)){
    print("Password can't be empty");
}
else if($Password !== $Password2){
    print("Password doesn't match, please retry.");
}else{
    $check = mysqli_fetch_row( $result );
    if($check[0] == $Email){
        print("Account already exist.");
    }else{
        $sql = "INSERT INTO users(Email, Password, Name) VALUES('$Email', '$Password', '$Name')";
        $conn->set_charset("utf8");
        $conn->query($sql);
        print('Account successfully created, please login');
        exit();
    }
}
$conn->close();
	
/*-----end connect-----*/
?>
