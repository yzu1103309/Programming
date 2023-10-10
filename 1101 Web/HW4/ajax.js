var Email;
var password;
    function progress() {
      Email = $("#Email").val();
      password = $("#password").val();
	    $.ajax({
		    url: "login.php",
		    data: {
		      Email: Email,
		      password: password
	      },
		    type: "POST",
		    datatype: "html",
	      success: function( output ) {
		      $( "#content" ).html(output);
	      },
		    error : function(){
		    alert( "Request failed." );
		    }
	    });
	  }
	  function add() {
      var todo = $("#todo").val();
      var date = $("#date").val();
	    $.ajax({
		    url: "add.php",
		    data: {
		      Email: Email,
		      todo: todo,
		      date: date
	      },
		    type: "POST",
		    datatype: "html",
	      success: function( output ) {
		      $( "#list" ).html(output);
	      },
		    error : function(){
		    alert( "Request failed." );
		    }
	    });
	  }
	  function deleteOne(count){
	    var str = '#num'+count;
      var num = $(str).val();
	    $.ajax({
		    url: "delete.php",
		    data: {
		        Email:Email,
		        num:num
	      },
		    type: "POST",
		    datatype: "html",
	      success: function( output ) {
		      $( "#list" ).html(output);
	      },
		    error : function(){
		    alert( "Request failed." );
		    }
	    });
	  }
	  
	  function edit(count){
	    var str = '#num'+count;
      var num = $(str).val();
	    $.ajax({
		    url: "edit.php",
		    data: {
		        Email:Email,
		        num:num
	      },
		    type: "POST",
		    datatype: "html",
	      success: function( output ) {
		      $( "#list" ).html(output);
	      },
		    error : function(){
		    alert( "Request failed." );
		    }
	    });
	  }
	  function save(count){
	    var str = '#num'+count;
      var num = $(str).val();
      var todo = $("#editT").val();
      var date = $("#editD").val();
	    $.ajax({
		    url: "save.php",
		    data: {
		        Email:Email,
		        num:num,
		        todo: todo,
		        date: date
	      },
		    type: "POST",
		    datatype: "html",
	      success: function( output ) {
		      $( "#list" ).html(output);
	      },
		    error : function(){
		    alert( "Request failed." );
		    }
	    });
	  }