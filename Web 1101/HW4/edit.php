<?php
$Num = $_POST['num'];
$Email = $_POST['Email'];
/*-----connect mysql-----*/

$conn = new mysqli('localhost', 'root', 'MushroomDawn','ToDoList');

if($conn->connect_error){
    die('Connection Failed : '.$conn->connect_error);
}else{

        $sql = "SELECT * FROM `list` WHERE `Email` LIKE '".$Email."'";
        $result = mysqli_query($conn,$sql);
        $count = 0;
        while($row = mysqli_fetch_row( $result )){
            if($Num == $row[3]){
                print('<tr> <td id="td1">"<input type="text" name="editT" id="editT" style="border:2px solid black; width:150px; font-size:15px;" value="'.$row[1].'" autofocus/>" must be done before
                <input type="date" name="editD" id="editD" style="border:2px solid black; width:150px; font-size:15px;" value="'.$row[2].'"></td>');
            }
            else if(date("Y-m-d")==$row[2]){
                print('<tr><td id="td1" style="color:red;">"'.$row[1].'" must be done before '.$row[2].'</td>');
            }else{
                print('<tr><td id="td1">"'.$row[1].'" must be done before '.$row[2].'</td>');
            }
            print('
            <td id="td2">
            <form><input type="text" name="num" id="num'.$count.'" value="'.$row[3].'" class="hidden" readonly>
            <input id = "submit" type="button" value = "Delete" class = "delete" onclick="deleteOne('.$count.')">');

            if($Num == $row[3]){
                print('<input id = "submit" type="button" value = "Save" class = "delete" onclick="save('.$count.')">');
            }else{
                print('<input id = "submit" type="button" value = "Edit" class = "delete" onclick="edit('.$count.')">');
            }

            print('</form>
            </td></tr>;');

            $count++;
    }

        $conn->set_charset("utf8");

        $conn->query($sql);
    }




$conn->close();

/*-----end connect-----*/
?>
