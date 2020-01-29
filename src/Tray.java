package octetos.core;

import octetos.core.Semver;

public class Tray
{
	static 
	{
    	System.loadLibrary("octetos-semver-java-100");
   	}
	private native boolean java_parser()
	{
		
	}
	public Semver version;
	public int dysplay_erro;
	public boolean parser()
	{
		return new HelloJNICpp().sayHello();
	}
}
