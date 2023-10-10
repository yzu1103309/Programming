<?php
$Email = $_POST['Email'];
$Password = $_POST['password'];
/*-----connect mysql-----*/

$conn = new mysqli('localhost', 'root', 'MushroomDawn','ToDoList');
$sql = "SELECT Password FROM users WHERE Email LIKE '".$Email."'";

if($conn->connect_error){
    die('Connection Failed : '.$conn->connect_error);
}else if(!( $result = mysqli_query($conn,$sql))){
    print("query error.");
}else{
    $check = mysqli_fetch_row( $result );
    if($check[0] === $Password && !empty($Password)){
        $sql = "SELECT Name FROM users WHERE Email LIKE '".$Email."'";
        $result = mysqli_query($conn,$sql);
        $name = mysqli_fetch_row( $result );
        print('


        <div id="DIV_BIG">
     <p><img id="banner" src="logo.png" alt="tilte"></p>
     <div id="link"><a href="index.html">LOG OUT</a></div>
    </div><h1 id="welcome">Welcome, '.$name[0].'. This is your to-do list...</h1>
    <table id="list">

    ');

    $sql = "SELECT * FROM `list` WHERE `Email` LIKE '".$Email."'";
    $result = mysqli_query($conn,$sql);
    $count = 0;
    while($row = mysqli_fetch_row( $result )){
        if(date("Y-m-d")==$row[2]){
            print('<tr><td id="td1" style="color:red;">"'.$row[1].'" must be done before '.$row[2].'</td>');
        }else{
            print('<tr><td id="td1">"'.$row[1].'" must be done before '.$row[2].'</td>');
            }
            print('
            <td id="td2">
            <form><input type="text" name="num" id="num'.$count.'" value="'.$row[3].'" class="hidden" readonly>
            <input id = "submit" type="button" value = "Delete" class = "delete" onclick="deleteOne('.$count.')">
            <input id = "submit" type="button" value = "Edit" class = "delete" onclick="edit('.$count.')">
            </form>
            </td></tr>');

    $count++;
    }


    print('

    </table>
    <div id="addEvent">
    <form>
      <h2>Task " <input type = "text" name="todo" id="todo" class="add" placeholder="Enter Task Here" required> " must be done before
       <input type = "date" name="date" id="date" class="add" required>
      <input id = "submit" type="button" value = "Add this to list" class="addbtn" onclick="add()">
      </h2>
    </form>
    </div>

    ');

    }else{
        print('
        
        
            <div id="DIV_BIG">
     <p>	<img id="banner" src="logo.png" alt="tilte" ></p>
     <div id="link"><a href="sign-up.html"> CREATE AN ACCOUNT </a></div>
    </div>
  <div>
    <h1>Login</h1>
        <div id="error">Invalid account or wrong password, please retry.</div>
  </div>
      <form>
      <div id=box1>
        <p class="form"><label for="Email"><b>Email</b></label><br>
        <input type="email" name="Email" id="Email" placeholder="Enter Email" required>
        </p>
        <p class="form">
        <label for="password"><b>Password</b></label><br>
        <input type="password" placeholder="Enter Password" name="password" id="password" required>
        </p>
        <input id = "submit" type="button" class="registerbtn" value = "Login" onclick="progress()">
      </div>
   </form>
   
   
        ');
    }
}
$conn->close();
	
/*-----end connect-----*/
?>
