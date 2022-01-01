<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
	<%@ page import="java.sql.*,java.io.*"%>
	<%
	// TODO Auto-generated method stub
		// get request parameters for userID and password
		String id = request.getParameter("user");
		String pwd = request.getParameter("pwd");
		Connection connect = null;
		Statement statement = null;
		ResultSet resultSet = null;

		try {

			// set path
			Class.forName("com.mysql.jdbc.Driver");

			connect = DriverManager.getConnection("jdbc:mysql://localhost:3306/batch2019?user=root&password=sanjay&useSSL=false");
			statement = connect.createStatement();

			// prepare query for first result
			resultSet = statement.executeQuery("select * from Employee where id = '" + id +"'");
			//resultSet.next();

			int flag = 0;
			while(resultSet.next()){
			String userId = resultSet.getString(1);
			String userName = resultSet.getString(2);
			String userSalary = resultSet.getString(3);
			String userPwd = resultSet.getString(4);
			if(pwd.equals(userPwd)){
			//out.println("Welcome: "+ userName);
			session.setAttribute("uName",userName); 
			String redirectURL = "welcome.jsp";
				response.sendRedirect(redirectURL);
				flag =1;
			}
				
			}
			if(flag==0){
				System.out.println("Wrong user id or password");

				String redirectURL = "HelloWorld.jsp";
				response.sendRedirect(redirectURL);
			}


			statement.close();
			connect.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		
	%>
	
</body>
</html>