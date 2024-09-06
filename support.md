<cl>Hey there! Glad to see you enjoy the mod. Now grab some water and read Kiba's thoughts on CBF and why he added the CBF blocker to Nullscapes at all. --Erymanthus</c>

-------------------------------------------------------------------------------------------------

So yeah. Nullscapes. That happened.

I just wanted to get my thoughts out there and clarify a couple things, especially with the drama surrounding the level and the CBF blocker I implemented. This post mainly serves the purpose of explaining exactly *why* I made the decisions I made leading up to the release of Nullscapes.

TL;DR, I'm not giving you one. Read the <cy>[darn]</c> pastebin.

First, I'd like to clarify a few things about the Click Between Frames mod itself and its comparison to the FPS bypass situation that occurred all those years ago. I've seen so much misinformation regarding CBF and FPS bypass throughout every CBF drama that's happened since the mod released, and I want to clear those up first. That's why the first part of this pastebin will be focusing on debunking two common misconceptions about CBF and its relationship to FPS bypass.

You might be wondering if I'm even qualified to talk about this sort of stuff since I'm not a "top player" by any means, but I do have a lot of knowledge in Geometry Dash coding and I've published many successful mods on the Geode index (including being one of the developers of Globed).


-------------------------------------------------------------------------------------------------


1. "CBF just makes inputs more precise, and it doesn't actually change the physics."

I can disprove this right off the bat since the CBF detector I introduced in Nullscapes... works. But for the sake of the argument, let's say that Nullscapes never existed to begin with.

Normally, physics steps in Geometry Dash happen every frame. In more technical terms, Geometry dash has a function called "PlayerObject::update(float dt)" which performs a physics step and "dt" is used to determine how much time since the previous frame has passed.

What we're interested in is the parameter that is passed to this function. Typically, GD will not change dt, or the "deltatime" of the physics step, (think of how most video games use delta time so that the game runs at the same speed no matter the framerate) under normal gameplay circumstances. However, CBF changes this parameter so that a new physics step is created sooner than it's supposed to--effectively changing the physics of the game.

Here is the relevant source code from CBF's Github page that demonstrates this behavior:

```
class $modify(PlayerObject) {
	void update(float timeFactor) {

		// ... some code

		const float newTimeFactor = timeFactor * step.deltaFactor;

		if (p1NotBuffering) {
				PlayerObject::update(newTimeFactor); // IMPORTANT!!! This line is what changes the physics!

		// ... more code
		}
	}
	
	// ... even more code
}
```

There are some additional functions in the CBF source code (not shown here) that use a custom "step" structure which tracks exactly when you click between physics steps so that it can apply the appropriate change to the timeFactor that's being passed in to the update(float) function.

Because CBF changes the value that is passed into the update function, and the update function controls the physics, this results in the CBF mod changing the physics of the game.




2. "CBF is like FPS bypass! If FPS bypass isn't cheating and was added to the game, why is CBF cheating?"

You're right in that FPS bypass isn't cheating and was added to the game. But we need to understand *why* it was considered legitimate. 

A lot of people seem to have forgotten that FPS bypass was actually bannable on the list for a fairly long period of time. For example, back when Sunix was a top player, he was banned from the list for a period of time because he used FPS bypass for his completions. It was only until PoweredByPie found out a way to gain the benefits of higher FPS on the vanilla GD client using external hardware that FPS bypass was eventually allowed for use on Pointercrate. I won't go into depth about "the piepass," but basically since FPS bypass was replicable in vanilla GD with no software modifications, it was eventually deemed legitimate and usable for list records.

Notice why FPS bypass was eventually allowed. It was because its effects were able to be reproduced with the vanilla GD client by simply replicating using a higher refresh-rate monitor--leveling the playing field. However, this is where the key difference between CBF and FPS bypass lies. The effects of CBF are not able to be reproduced in vanilla GD.

Even if we assume that TPS isn't locked to 240fps and that physics steps occur every frame no matter the deltatime, the only way to replicate CBF in vanilla GD would be to purchase and use an Infinite-Hz refresh-rate monitor, or at least one that's equal to the polling rate of your input device (which for a sayodevice is in the range of around 8000 Hz). Last time I checked, such a monitor doesn't exist and probably won't until the heat death of the universe.


-------------------------------------------------------------------------------------------------


Now that I've gotten those out of the way, I'll be dedicating this part of the pastebin to explaining why I made the choices I made for including the CBF blocker in Nullscapes.

When I first gave Zoink the verification in March, CBF was an afterthought since... well it didn't exist at the time. CBF was released in April and some talk surrounding it ensued, but neither Zoink or I worried about it too much. Eventually it got to the point where CBF was allowed for the list sometime in late June despite RobTop's active disproval of the mod where we both got confused. Logically, CBF was cheating since it objectively made the game easier (especially for low-frame-window inputs or frame perfects where the mod gives you more time after the last available frame to click without dying--something that's very common in Nullscapes).

So, we talked about it. Eventually, Zoink brought up to me his feelings regarding CBF and Nullscapes. Obviously I wanted the level rated, so him verifying the level with CBF was off the table. He also told me that he was uncomfortable with verifying the level without CBF since "the first victor will come so much faster because they can do it with cbf."

I was faced with a dilemma. I could either let Zoink verify Nullscapes with CBF--risking the level not getting rated but keeping it fair between him and the playerbase, or I could disallow him to use CBF and allow the level to get rated, but make things unfair. Especially for a level such as Nullscapes--with it being the first level since CBF was allowed, in the difficulty range where using it would actually matter--this was a really hard decision to make.

Ultimately, I ended up making a decision that to me, sounded like the best of both worlds. This is where the idea of the CBF blocker came in to play, as Zoink and I were ideating on ways we could implement it. Other levels have used noclip anticheats at the end of levels for years, so I felt a CBF blocker would be appropriate. That way, Zoink would be able to verify Nullscapes without CBF, allowing for the level to be rated, while keeping the playing field even between him and the playerbase.

It took a while for me to actually find a setup that worked for the level though, around a month to be exact. The CBF blocker was actually a fairly last-minute addition to the level with it being added near the end of July. I showed the CBF detector to him and we were both pleased with the result.

The original intention was to keep the CBF blocker a secret until the level was finally released. But as you know, that didn't go as smoothly as I'd hoped.


-------------------------------------------------------------------------------------------------


This is definitely the part of the situation where I could've handled it more maturely than I did. I "teased" the idea of a CBF blocker in the level on one of Zoink's progress tweets, and it blew up in my face instantly. I quite honestly did not expect the response that the general GD community had about it, and I definitely didn't expect people to find out so quickly. I should've saw it coming though, especially considering how sensitive the CBF debate was at the time.

Since the cat was out of the bag, I ended up making some jokes about CBF and the blocker I added to the level itself. A lot of these were bait, but some were made as genuine outlets of frustration I had with the mod and how difficult it made things for Nullscapes as a whole.

Eventually, Nullscapes was released to the public and here we are today, over two years after the level's first inception. And as expected, it blew up in my face again. In hindsight, it probably was a good thing that I teased the CBF blocker earlier, as if I hadn't and people weren't expecting it--I think I would've gotten at least 3-4x the harassment, hate comments, and death threats as I'm getting now. It's kindof sad that I've desensitized myself to those sorts of comments over my time here in this community, but oh well. Gotta lock in, y'know?

So, what did I learn about this? Well, a couple things.

First is the general lack of respect the community seems to have towards level creators. Not just towards me but to others as well. OniLink is the most recent example of this, simply posting some screenshots of their upcoming level and getting dogged on in the comments. I had some criticisms about the colors used in the level itself, but ultimately I tried to frame it in a constructive manner and others should do the same. I also see countless other creators get their works shamed in public spaces, even if they are just asking for feedback. I think overall the creating scene has become much more toxic over the years, especially towards harder levels where every aspect of the level has to be "perfect" for any top player to even remotely enjoy it.

Second is the way-too-apparent separation of art from artist, or at least that's the best way I can describe it. Levels don't just "appear." People have to take time out of their day, week, month, or year, to make them. There are tens of thousands of design decisions, conscious or not, that go into every Geometry Dash level you see on the featured tab, and ultimately, creators have the right to every object in their level and we need to respect that. Just like how top players say us creators should have no say about top play, we could say the same thing--you top players should have no say in what we put in our levels. Sure, you might not agree with the fact that I included a CBF blocker in Nullscapes, but at the end of the day it's my level and if I don't want people using a mod that RobTop himself disapproves of, then it's my decision. It's okay to not like the level because of that. Or if you want to use CBF, just play the level in a copy. I know that I definitely could've handled the situation better, and I know that the harassment I received probably won't be reciprocated for other levels with CBF blockers, such as The Yangire and Kosetsu, since I'm ultimately the one who started it (oops!). But I feel like a lot of the harassment thrown my way was just unnecessary for a level in a video game.


-------------------------------------------------------------------------------------------------


I'm not a CBF hater. Never was. I think CBF is good for the game and it would be awesome to see it added since it would actually level out the playing field once and for all. But as it stands now, I believe that it's cheating and I won't be removing the CBF blocker from Nullscapes. However, I will concede that I did go too far with the whole "loser!" wording I used in the level, so I'll be removing that. I'm also lowering the attempt count required to actually transition from the Shardscapes intro to the level itself, since a lot of people seem to think that was the CBF blocker this whole time.

If you made it to the end, thank you so much for taking time out of your day to read this. This was kindof just an emotion dump mixed in with some technical jargon that I'm wishfully thinking people will understand, but oh well.