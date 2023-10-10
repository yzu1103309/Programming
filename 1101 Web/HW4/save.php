<?php
$Email = $_POST['Email'];
$Task = $_POST['todo'];
$Date = $_POST['date'];
$Num = $_POST['num'];
/*-----connect mysql-----*/

$conn = new mysqli('localhost', 'root', 'MushroomDawn','ToDoList');

if($conn->connect_error){
    die('Connection Failed : '.$conn->connect_error);
}else{
    if(empty($Email)){
        print('error account');
    }else if(empty($Task)){
        print('Please set a task');
    }
    else if(empty($Date)){
        print('Please choose a date');
    }else{

        $sql = "UPDATE `list` SET Task='$Task',Date='$Date' WHERE Num=$Num";

        $conn->set_charset("utf8");

        $conn->query($sql);
    }


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

}
$conn->close();

/*-----end connect-----*/
?>
