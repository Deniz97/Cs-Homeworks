package ceng.ceng351.stackoverflowdb;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
Here is your MySQL account:
user name: e2172088    password: b34d83    schema(database): db2172088

Host: 144.122.71.165
Port: 3306
**/

public class STACKOVERFLOWDB implements ISTACKOVERFLOWDB {
	
	private Connection conn = null;
	
	private static String user = "e2172088";  
    private static String password = "b34d83";
    private static String host = "144.122.71.165";
    private static String database = "db2172088";
    private static int port = 3306;
    
	
	
	public void initialize(){
		
		String url = "jdbc:mysql://" + this.host + ":" + this.port + "/" + this.database;
		try {
            Class.forName("com.mysql.jdbc.Driver");
            this.conn =  DriverManager.getConnection(url, this.user, this.password);
            
            
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
		
	}
	
	public int createTables(){
		
		int result;
		int numberofTablesCreated = 0;
		String queryCreateTable = "";
	
		//drop tables
		//dropTables();
		queryCreateTable="create table IF NOT EXISTS  user  (userID varchar(10),username varchar(30),"
				+ "registrationDate date,lastLoginDate date,Primary Key(userID))";
		try {
			Statement stmnt = this.conn.createStatement();
				result = stmnt.executeUpdate(queryCreateTable);
				if(result==1){ numberofTablesCreated++; }
				//close
				stmnt.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
		
		queryCreateTable="create table IF NOT EXISTS article (articleID varchar(10),"
				+ "userID varchar(10),name varchar(80),description varchar(130),"
				+ "date date,rating int,primary key(articleID),"
				+ "foreign key(userID) references user(userID) on delete cascade on update cascade)";
		try {
			Statement stmnt = this.conn.createStatement();
				result=stmnt.executeUpdate(queryCreateTable);
				if(result==1){ numberofTablesCreated++; }
				//close
				stmnt.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
		queryCreateTable="create table IF NOT EXISTS comment (commentID varchar(10),"
				+ "articleID varchar(10), userID varchar(10), message varchar(130),"
				+ "date date,rating int,primary key(commentID),"
				+ "foreign key(userID) references user(userID) on delete cascade on update cascade,"
				+ "foreign key(articleID) references article(articleID) on delete cascade on update cascade)";
		try {
			Statement stmnt = this.conn.createStatement();
				result = stmnt.executeUpdate(queryCreateTable);
				if(result==1){ numberofTablesCreated++; }
				//close
				stmnt.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
		queryCreateTable="create table IF NOT EXISTS reputation (reputationID varchar(10),"
				+ "userID varchar(10),weeklyReputation int,monthlyReputation int,"
				+ "yearlyReputation int,alltimeReputation int, primary key(reputationID),"
				+ "foreign key(userID) references user(userID) on delete cascade on update cascade)";
		try {
			Statement stmnt = this.conn.createStatement();
				result = stmnt.executeUpdate(queryCreateTable);
				if(result==1){ numberofTablesCreated++; }
				//close
				stmnt.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
		
		
		
		return numberofTablesCreated;
		
	}
	
	public int dropTables(){
		
		int numberofTablesDropped = 0;
		int i = 0;
		
		String queryDropTable = "";

		String[] keys = {"reputation","comment","article","user"};
	
		while(i<4){
			
			try {
				Statement statement = this.conn.createStatement();
				queryDropTable = "drop table if exists " + keys[i];
				
				statement.executeUpdate(queryDropTable);
				numberofTablesDropped++;
				//close
				statement.close();
				i++;
				
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
		}
		
		
		return numberofTablesDropped;
		
	}
	
	public int insertUser( User[] users  ){
		
		int len = users.length;int  i=0;
		int correctly_inserted = 0;
		int result;
		while(i<len){
			String sql="";
			if(users[i].getusername()==""){
				 sql ="insert into user values('"+users[i].getuserID()+"',"+
						"NULL"+",'"+
						users[i].getregistrationDate()+"','"+
						users[i].getlastLoginDate()+"')"; 
			}else{
			
			
				sql = "insert into user values('"+users[i].getuserID()+"','"+
					users[i].getusername()+"','"+
					users[i].getregistrationDate()+"','"+
					users[i].getlastLoginDate()+"')";
			}
			try {
				Statement stmnt = this.conn.createStatement();
				result = stmnt.executeUpdate(sql);
				//close
				stmnt.close();
				if(result==1){
					correctly_inserted++;
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
			i++;
		}
		return correctly_inserted;
	}
	
	public int insertArticle(  Article[] articles ){
		
		int len = articles.length;int  i=0;
		int correctly_inserted = 0;
		int result;
		while(i<len){
			String artID="";
			String usID="";
			String name="";
			String des="";
			if(articles[i].getarticleID()==""){
				artID="NULL";
			}
			else{
				artID="'"+articles[i].getarticleID()+"'";
			}
			if(articles[i].getuserID()==""){
				usID="NULL";
			}
			else{
				usID="'"+articles[i].getuserID()+"'";
			}
			if(articles[i].getname()==""){
				name="NULL";
			}
			else{
				name="\""+articles[i].getname()+"\"";
			}
			if(articles[i].getdescription()==""){
				des="NULL";
			}
			else{
				des="\""+articles[i].getdescription()+"\"";
			}
			
			String sql = "insert into article values("+artID+","+
					usID+","+
					name+","+
					des+",'"+
					articles[i].getdate()+"',"+
					articles[i].getrating()+")";
			try {
				Statement stmnt = this.conn.createStatement();
				result = stmnt.executeUpdate(sql);
				//close
				stmnt.close();
				if(result==1){
					correctly_inserted++;
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
			i++;
			
		}
		return correctly_inserted;
		
	}
	
	public int insertComment(  Comment[] comments ){
		
		int len = comments.length;int  i=0;
		int correctly_inserted = 0;
		int result;
		while(i<len){
			
			String artID="";
			String usID="";
			String comID="";
			String mes="";
			if(comments[i].getarticleID()==""){
				artID="NULL";
			}
			else{
				artID="'"+comments[i].getarticleID()+"'";
			}
			if(comments[i].getuserID()==""){
				usID="NULL";
			}
			else{
				usID="'"+comments[i].getuserID()+"'";
			}
			if(comments[i].getcommentID()==""){
				comID="NULL";
			}
			else{
				comID="'"+comments[i].getcommentID()+"'";
			}
			if(comments[i].getmessage()==""){
				mes="NULL";
			}
			else{
				mes="\""+comments[i].getmessage().replace("\"", "\"\"")+"\"";
			}
			
			String sql = "insert into comment values("+comID+","+
					artID+","+
					usID+","+
					mes+",'"+
					comments[i].getdate()+"',"+
					comments[i].getrating()+")";
			try {
				Statement stmnt = this.conn.createStatement();
				result = stmnt.executeUpdate(sql);
				//close
				stmnt.close();
				if(result==1){
					correctly_inserted++;
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
			i++;
			
		}
		return correctly_inserted;
		
	}
	
	public int insertReputation(Reputation[] reputations){
		

		int len = reputations.length;int  i=0;
		int correctly_inserted = 0;
		int result;
		while(i<len){
			String repID="";
			String usID="";
			if(reputations[i].getuserID()==""){
				usID="NULL";
			}
			else{
				usID="'"+reputations[i].getuserID()+"'";
			}
			if(reputations[i].getreputationID()==""){
				repID="NULL";
			}
			else{
				repID="'"+reputations[i].getreputationID()+"'";
			}
			String sql = "insert into reputation values("+repID+","+
					usID+","+
					reputations[i].getweeklyReputation()+","+
					reputations[i].getmonthlyReputation()+","+
					reputations[i].getyearlyReputation()+","+
					reputations[i].getalltimeReputation()+")";
			try {
				Statement stmnt = this.conn.createStatement();
				result = stmnt.executeUpdate(sql);
				//close
				stmnt.close();
				if(result==1){
					correctly_inserted++;
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
			i++;
			
		}
		return correctly_inserted;
		
	}
	
	public QueryResult.UsernameDateRatingResult[] getArticleHighestRating(){
		
		String query;
		ResultSet result = null;
		query="SELECT u.username, a.date, a.rating FROM user u,"
				+ " article a WHERE u.userID=a.userID and a.rating in "
				+ "( SELECT max(a1.rating) FROM article a1) ORDER BY u.username";
		
		//get the result set.
		try {
			Statement stmnt = this.conn.createStatement();
			result = stmnt.executeQuery(query);
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//get the row count
		int rowcount = 0;
		  try{
			  result.last(); 
			  rowcount = result.getRow();
			  result.beforeFirst(); 
		  }catch(SQLException e){
				  e.printStackTrace();
		  }
		  QueryResult.UsernameDateRatingResult[] my_array= new QueryResult.UsernameDateRatingResult[rowcount]; 
		
		//iterate the result set
		int i=0;
		  try {
			result.first();
			do{if(rowcount==0){break;}
				String m_username=result.getString("username");
				String m_date = result.getString("date");
				int m_rating = result.getInt("rating");
				my_array[i] = new QueryResult.UsernameDateRatingResult(m_username,m_date,m_rating);
				i++;
			}while( result.next()==true);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return my_array;
		  
	}
	
	public QueryResult.UsernameMessageRatingAlltimereputationResult[] getCommentLowestRating(){
	
		String query;
		ResultSet result = null;
		query="SELECT u.username, c.message, c.rating, r.alltimeReputation "
				+ "FROM user u, comment c, reputation r"
				+ " WHERE u.userID=c.userID and u.userID=r.userID and c.message"
				+ " NOT LIKE '%mysql%' and c.rating= "
				+ "(SELECT min(c1.rating) FROM comment c1"
				+ " WHERE c1.message NOT LIKE '%mysql%')"
				+ " ORDER BY username";
		
		//get the result set.
		try {
			Statement stmnt = this.conn.createStatement();
			result = stmnt.executeQuery(query);
			//stmnt.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//get row count
		int rowcount=0;
		  try{
			  result.last(); 
			  rowcount = result.getRow();
			  result.beforeFirst(); 
		  }catch(SQLException e){
				  e.printStackTrace();
		  }
		//iterate the result set
				  QueryResult.UsernameMessageRatingAlltimereputationResult[] my_array = new QueryResult.UsernameMessageRatingAlltimereputationResult[rowcount];
		try {
			result.first();
			int i=0;
			do{if(rowcount==0){break;}
				String m_username= result.getString("username");
				String m_message=result.getString("message");
				int m_rating=result.getInt("rating");
				int m_atRep=result.getInt("alltimeReputation");
				my_array[i]= new QueryResult.UsernameMessageRatingAlltimereputationResult(m_username, m_message, m_rating, m_atRep);
				i++;
			}while( result.next()==true);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return my_array;
		
	}
	
	public QueryResult.UseridUsernameRegistrationdateWeeklyreputationResult[]  getUseridUsernameAfterGivenDate(String Date){
		
		String query;
		ResultSet result = null;
		query="SELECT u.userID, u.username, u.registrationDate, r.weeklyReputation "
				+ "FROM user u, reputation r WHERE u.userID=r.userID and "
				+ "u.registrationDate > '"+Date+"' ORDER BY u.userID";
		
		//get the result set.
		try {
			Statement stmnt = this.conn.createStatement();
			result = stmnt.executeQuery(query);
			//stmnt.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//get row count
		int rowcount=0;
		  try{
			  result.last(); 
			  rowcount = result.getRow();
			  result.beforeFirst(); 
		  }catch(SQLException e){
				  e.printStackTrace();
		  }
		//iterate the result set
		  QueryResult.UseridUsernameRegistrationdateWeeklyreputationResult[] my_array = new QueryResult.UseridUsernameRegistrationdateWeeklyreputationResult[rowcount];
			try {
				result.first();
				int i=0;
				do{if(rowcount==0){break;}
					String m_userID=result.getString("userID");
					String m_username = result.getString("username");
					String m_rDate = result.getString("registrationDate");
					int m_wRep= result.getInt("weeklyReputation");
					my_array[i]= new QueryResult.UseridUsernameRegistrationdateWeeklyreputationResult(m_userID, m_username, m_rDate, m_wRep);
					i++;
				}while( result.next()==true);
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			return my_array;
		
	}
	
	public QueryResult.UsernameMessageRatingResult[]  getUsernameMessageRatingMoreThanGivenRating(String message, int rating){
		String query;
		ResultSet result = null;
		query="SELECT u.username, c.message, c.rating"
				+ " FROM user u, comment c WHERE u.userID=c.userID and"
				+ " c.message NOT LIKE '%"+message+"%' and "
				+ "c.rating > "+rating+" ORDER BY u.username";
		
		//get the result set.
		try {
			Statement stmnt = this.conn.createStatement();
			result = stmnt.executeQuery(query);
			//stmnt.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//get row count
				int rowcount=0;
				  try{
					  result.last(); 
					  rowcount = result.getRow();
					  result.beforeFirst(); 
				  }catch(SQLException e){
						  e.printStackTrace();
				  }
				//iterate the result set
				  QueryResult.UsernameMessageRatingResult[] my_array = new QueryResult.UsernameMessageRatingResult[rowcount];
					try {
						result.first();
						int i=0;
						do{if(rowcount==0){break;}
							String m_username=result.getString("username");
							String m_message = result.getString("message");
							int m_rating = result.getInt("rating");
							my_array[i]= new QueryResult.UsernameMessageRatingResult(m_username, m_message, m_rating);
							i++;
						}while( result.next()==true);
					} catch (SQLException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					return my_array;
		
	}
	
	public int  MultiplyComment(String date){
		
		String query;
		ResultSet result = null;
		query="SELECT c.commentID FROM comment c WHERE c.date>'"+date+"'";
		
		//execute update
		try {
			Statement stmnt = this.conn.createStatement();
			result = stmnt.executeQuery(query);
			//stmnt.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//get row count
				int rowcount=0;
				  try{
					  result.last(); 
					  rowcount = result.getRow();
					  result.beforeFirst(); 
				  }catch(SQLException e){
						  e.printStackTrace();
				  }
				  query="UPDATE comment SET rating = rating*2 WHERE date > '"+date+"'";
				  try{
					  Statement stmnt = this.conn.createStatement();
					  stmnt.executeUpdate(query);
					  stmnt.close();
				  }catch(SQLException e){
					  e.printStackTrace();
				  }
				  
				  return rowcount;
	}
	
	public QueryResult.UseridUsernameLastlogindateResult[]  getUsernameMessageRatingCommentedByGivenUser(String userID){
		String query;
		ResultSet result = null;
		
		query="SELECT u.userID, u.username, u.lastLoginDate "
				+ "FROM user u WHERE u.userID!='"+userID+"' and "
				+ "NOT EXISTS (SELECT c1.articleID FROM comment c1, user u1 "
				+ "WHERE c1.userID='"+userID+"' and c1.articleID NOT IN (SELECT c2.articleID FROM comment c2 "
						+ "WHERE c2.userID=u.userID)) ORDER BY u.userID";
		
		
		//get the result set.
		try {
			Statement stmnt = this.conn.createStatement();
			result = stmnt.executeQuery(query);
			//stmnt.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//get row count
				int rowcount=0;
				  try{
					  result.last(); 
					  rowcount = result.getRow();
					  result.beforeFirst(); 
				  }catch(SQLException e){
						  e.printStackTrace();
				  }
				//iterate the result set
				  QueryResult.UseridUsernameLastlogindateResult[] my_array = new QueryResult.UseridUsernameLastlogindateResult[rowcount];
					try {
						result.first();
						int i=0;
						do{if(rowcount==0){break;}
							String m_userID=result.getString("userID");
							String m_username=result.getString("username");
							String m_llDate = result.getString("lastLoginDate");
							my_array[i]= new QueryResult.UseridUsernameLastlogindateResult(m_userID, m_username, m_llDate);
							i++;
						}while( result.next()==true);
					} catch (SQLException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					return my_array;
	}
	
	public QueryResult.UsernameMessageRatingResult[]  getNameUsernameDateRatingMoreThanGivenArticle(int rating, String articleID){
		
		String query;
		ResultSet result = null;
		query="SELECT u.username, c.message, c.rating"
				+ " FROM user u, comment c WHERE u.userID=c.userID and"
				+ " c.articleID='"+articleID+"'and c.rating>"+rating+" ORDER BY u.username";
		
		//get the result set.
		try {
			Statement stmnt = this.conn.createStatement();
			result = stmnt.executeQuery(query);
			//stmnt.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//get row count
				int rowcount=0;
				  try{
					  result.last(); 
					  rowcount = result.getRow();
					  result.beforeFirst(); 
				  }catch(SQLException e){
						  e.printStackTrace();
				  }
				//iterate the result set
				  QueryResult.UsernameMessageRatingResult[] my_array = new QueryResult.UsernameMessageRatingResult[rowcount];
					try {
						result.first();
						int i=0;
						do{if(rowcount==0){break;}
							String m_username=result.getString("username");
							String m_message = result.getString("message");
							int m_rating = result.getInt("rating");
							my_array[i]= new QueryResult.UsernameMessageRatingResult(m_username, m_message, m_rating);
							i++;
						}while( result.next()==true);
					} catch (SQLException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					return my_array;
	}
	public QueryResult.NameUsernameDateRatingResult[]  getUsernameDateRatingNotCommentedByAnyUser(){
		String query;
		ResultSet result = null;
		query="SELECT a.name, u.username, a.date, a.rating "
				+ "FROM user u, article a, comment c WHERE c.userID=u.userID and c.articleID=a.articleID "
				+ "and NOT EXISTS (SELECT c1.commentID FROM comment c1 "
				+ "WHERE c1.articleID=a.articleID and c1.userID!=u.userID) ORDER BY a.name";
		
		//get the result set.
		try {
			Statement stmnt = this.conn.createStatement();
			result = stmnt.executeQuery(query);
			//stmnt.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//get row count
				int rowcount=0;
				  try{
					  result.last(); 
					  rowcount = result.getRow();
					  result.beforeFirst(); 
				  }catch(SQLException e){
						  e.printStackTrace();
				  }
				//iterate the result set
				  QueryResult.NameUsernameDateRatingResult[] my_array = new QueryResult.NameUsernameDateRatingResult[rowcount];
					try {
						result.first();
						int i=0;
						do{if(rowcount==0){break;}
							String m_name = result.getString("name");
							String m_username = result.getString("username");
							String m_date = result.getString("date");
							int m_rating = result.getInt("rating");
							my_array[i]= new QueryResult.NameUsernameDateRatingResult(m_name, m_username, m_date, m_rating);
							i++;
						}while( result.next()==true);
					} catch (SQLException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					return my_array;
	}
	
	public QueryResult.UsernameDateRatingResult[]  UsernameDateRatingHasHighestReputation(String date){
		String query;
		ResultSet result = null;
		query="SELECT DISTINCT u.username, a.date, a.rating "
				+ "FROM user u, article a, comment c, reputation r "
				+ "WHERE u.userID=a.userID and a.date<'"+date+"'and r.userID=u.userID and r.weeklyReputation="
				+ " ( SELECT max(r1.weeklyReputation) 	FROM reputation r1,article a1 "
				+ "	WHERE a1.date<'"+date+"' and r1.userID=a1.userID )"
				+ " ORDER BY u.username";
		
		//get the result set.
		try {
			Statement stmnt = this.conn.createStatement();
			result = stmnt.executeQuery(query);
			//stmnt.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//get row count
				int rowcount=0;
				  try{
					  result.last(); 
					  rowcount = result.getRow();
					  result.beforeFirst(); 
				  }catch(SQLException e){
						  e.printStackTrace();
				  }
				//iterate the result set
				  QueryResult.UsernameDateRatingResult[] my_array = new QueryResult.UsernameDateRatingResult[rowcount];
					try {
						result.first();
						int i=0;
						do{if(rowcount==0){break;}
							String m_username = result.getString("username");
							String m_date = result.getString("date");
							int m_rating = result.getInt("rating");
							my_array[i]= new QueryResult.UsernameDateRatingResult( m_username, m_date, m_rating);
							i++;
						}while( result.next()==true);
					} catch (SQLException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					return my_array;
	}
	
	public QueryResult.UsernameDateRatingResult[]  UsernameDateRatingDeleteAndSelect(String date){
		String query;
		ResultSet result = null;
		
			//delete operation
			query="DELETE FROM article WHERE date>'"+date+"'";
			try{
				Statement stmnt=this.conn.createStatement();
				stmnt.executeUpdate(query);
			}catch(SQLException e){
				e.printStackTrace();
			}
			//Get the remaining rows
			query="SELECT u.username,  a.date, a.rating "
					+ "FROM user u, article a "
					+ "WHERE u.userID=a.userID ORDER BY u.username";
			//get the result set.
			try {
				Statement stmnt = this.conn.createStatement();
				result = stmnt.executeQuery(query);
				//stmnt.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			//get result count
				int rowcount=0;
				  try{
					  result.last(); 
					  rowcount = result.getRow();
					  result.beforeFirst(); 
				  }catch(SQLException e){
						  e.printStackTrace();
				  }
			
			//iterate the result set
			  QueryResult.UsernameDateRatingResult[] my_array = new QueryResult.UsernameDateRatingResult[rowcount];
				try {
					result.first();
					int i=0;
					do{if(rowcount==0){break;}
						String m_username = result.getString("username");
						String m_date = result.getString("date");
						int m_rating = result.getInt("rating");
						my_array[i]= new QueryResult.UsernameDateRatingResult( m_username, m_date, m_rating);
						i++;
					}while( result.next()==true);
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				return my_array;
	}	


	
		
	
	
	
	
	
	
	
}
