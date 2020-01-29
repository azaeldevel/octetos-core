package octetos.core;

public class Semver
{
	public short major;
	public short minor;
	public short patch;
	public String prerelease;
	public String build;

	@Override
    public String toString()
	{
		return "--";
	}
	
	public void init()
	{
		major = -1;
		minor = -1;
		patch = -1;
		prerelease = "";
		build = "";
	}
	
	public Semver()
	{
		//System.out.println("Hello World Semver!");
	}
}
