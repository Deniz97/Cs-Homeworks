public class CengGift 
{
	private Integer key;
	
	private String name;
	private String material;
	private String color;
	
	public CengGift(Integer key, String name, String material, String color)
	{
		this.key = key;
		this.name = name;
		this.material = material;
		this.color = color;
	}
	
	// Getters
	
	public Integer key()
	{
		return key;
	}
	public String name()
	{
		return name;
	}
	public String material()
	{
		return material;
	}
	public String color()
	{
		return color;
	}
	
	// GUI method - do not modify
	public String fullName()
	{
		return "" + key() + "|" + name() + "|" + material() + "|" + color();
	}
	
	// DO NOT ADD SETTERS
}
